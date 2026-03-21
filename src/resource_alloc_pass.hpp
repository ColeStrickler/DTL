#ifndef RSRC_ALLOC_PASS_HPP
#define RSRC_ALLOC_PASS_HPP
#include "resource_analysis_pass.hpp"
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "util.hpp"


namespace DTL
{

#define WRITE_BOOL(addr, value)(*(bool*)(addr) = value)
#define WRITE_UINT8(addr, value)(*(uint8_t*)(addr) = value)
#define WRITE_UINT16(addr, value)(*(uint16_t*)(addr) = value)
#define WRITE_UINT32(addr, value)(*(uint32_t*)(addr) = value)
#define WRITE_UINT64(addr, value)(*(uint64_t*)(addr) = value)

#define READ_BOOL(addr)(*(bool*)(addr))
#define READ_UINT8(addr)(*(uint8_t*)(addr))
#define READ_UINT16(addr)(*(uint16_t*)(addr))
#define READ_UINT32(addr)(*(uint32_t*)(addr))
#define READ_UINT64(addr)(*(uint64_t*)(addr))
#define READ_INT32(addr)(*(int*)(addr))


#define USED_OUTSTMT_REG 0xf01
#define USED_FORLOOP_REG 0xf02
#define USED_OUT_PERCOND_REG 0xf03
#define USE_CONDITIONAL_REG 0xf04
#define USE_CONDITIONAL_IDX_REG 0xf05
#define USE_CONDITIONAL_ISEVEN_REG 0xf06


inline int log2ceil(int n) {
    if (n <= 0) {
        // Handle error or return a specific value for non-positive input
        return 0; // Or throw an exception
    }
    return static_cast<int>(std::ceil(std::log2(static_cast<double>(n))));
}

template<typename T>
T divceil(T a, T b) {
    if (b == 0) throw std::invalid_argument("division by zero");

    if ((a ^ b) > 0) // same sign
        return (a + b - 1) / b;
    else
        return a / b;
}
inline std::string to_hex(uint64_t val) {
    std::stringstream ss;
    ss << "0x" << std::hex << std::setw(16) << std::setfill('0') << val;
    return ss.str();
}
struct LoopReg
{
    int init_value;
    int increment_condition;
    int reg_num;
    Magic hwDivMagic;
};

struct ConstArray
{
    std::vector<uint32_t> values; 
    int reg_num;
    int index_reg_num;
};


struct LayerConfig
{
    int nAdd;
    int nMult;
    int nSub;
    int nPassThru;
};



// probably want to make a parameters struct to pass in
class AGUHardwareStat
{
public:
    AGUHardwareStat(const std::vector<LayerConfig>& layerCfg, int nLayers, int nConst, int nForLoop, int nOutStatements, int nConstArray, int bytes_cell = 2) :\
       nConstRegisters(nConst), nForLoopRegisters(nForLoop),\
        nLayers(nLayers), nOutStatements(nOutStatements), nConstArray(nConstArray),\
        nConstArraySize(32), nMaxConfigs(1), layerCfgs(layerCfg)
    {
                assert(layerCfg.size() == nLayers+1);
        /*
            1 config per out statement,
            1 routing config per layer,
            nMult, nAdd, nPassThrough per layer


            we will make each cell have 4 valid outs a byte wide
        */
        bytesMagic = 16;
        bytesCell = bytes_cell;
        bytesLayer = bytesCell * (GetMaxFuncUnits());

        
        idxBit = log2ceil(GetMaxFuncUnits()+1); // We do not need +1, because we are zero indexed


        bytesOutStatement = (nLayers+1) * bytesLayer; // layer at beginning at at the end
        totalConfigRegionBits = nOutStatements * bytesOutStatement;
    }

    ~AGUHardwareStat()
    {

    }

    /*
        [AddUnits, MultUnits, PassThru]
    */
    void WriteConfig(uint64_t baseAddress, int numOutStatement, int layer, int inRegNumber, int outRegNumber)
    {
        unsigned int layerByteOffset = layer * bytesLayer;
        unsigned int cellByteOffset = inRegNumber * bytesCell;
        unsigned int outStatementOffset = numOutStatement * bytesOutStatement;

        assert(outRegNumber < __UINT8_MAX__);

        /*
            We call each in->out routing config a "Cell".

            Each Cell is 1 byte
        */

        WRITE_UINT8(baseAddress + layerByteOffset + cellByteOffset + outStatementOffset, static_cast<unsigned char>(outRegNumber));
    }


    inline uint64_t GetLoopRegsOffset() const
    {
        return static_cast<uint64_t>(nOutStatements*(nLayers+1)*(GetMaxFuncUnits())*bytesCell);
    }

    inline uint64_t GetLoopIncRegsOffset(uint32_t byteWidth) const
    {
        return GetLoopRegsOffset() + (nForLoopRegisters*byteWidth);
    }

    inline uint64_t GetConstantRegsOffset(uint32_t byteWidth) const
    {
        return GetLoopIncRegsOffset(byteWidth) + (nForLoopRegisters*byteWidth);
    }


    inline uint64_t GetConstArrayOffset(uint32_t byteWidth) const 
    {
        return GetConstantRegsOffset(byteWidth) + (nConstRegisters*byteWidth);
    }

    inline uint64_t GetMagicRegsOffset(uint32_t byteWidth) const
    {
                                            // we do +8 because we need to align on 64bit words the 64bit magic register that comes next
        return alignTo8(GetConstArrayOffset(byteWidth) + (nConstArray*nConstArraySize*byteWidth + 8));
    }
    
   


    void DoForLoopWrite(uint64_t baseAddress, LoopReg& reg, uint32_t byte_width);
    


    /*
        We will return both the inc register write and the for loop write
    */
    std::string PrintForLoopWrite(uint64_t baseAddress, LoopReg& reg, uint32_t byte_width);
    
    void DoConstRegWrite(uint64_t baseAddress, int constRegNum, int constRegvalue, uint32_t byte_width)
    {
       printf("ConstRegOffset() 0x%x, 0x%x\n",  GetConstantRegsOffset(byte_width), GetConstantRegsOffset(byte_width) + constRegNum*byte_width);
        uint64_t addr_ = baseAddress + GetConstantRegsOffset(byte_width) + constRegNum*byte_width;
         
        assert(byte_width == 4);
        WRITE_UINT32(addr_, constRegvalue);
    }

    std::string PrintConstRegWrite(uint64_t baseAddress, int constRegNum, int constRegvalue, uint32_t byte_width)
    {
         printf("ConstRegOffset() 0x%x, 0x%x\n",  GetConstantRegsOffset(byte_width), GetConstantRegsOffset(byte_width) + constRegNum*byte_width);
        uint64_t addr_ = baseAddress + GetConstantRegsOffset(byte_width) +constRegNum*byte_width;
        std::string addr = to_hex(addr_);



        uint64_t write_value_ = constRegvalue;
        std::string write_value = to_hex(write_value_);

        // ret to loop register
        std::string ret = "WRITE_UINT32(" + addr + "," + write_value + ");";
        return ret;
    }


    std::string PrintConstArrayWrite(uint64_t baseAddress, ConstArray& constArray, uint32_t byte_width)
    {
        printf("Const array offset 0x%x\n", GetConstArrayOffset(byte_width));
        uint64_t baddr = baseAddress + GetConstArrayOffset(byte_width);// + constArray.reg_num*(nConstArraySize*byte_width + 8);

        std::string ret;
        for (int i = 0; i < constArray.values.size(); i++)
        {
            auto& cval = constArray.values[i];
            assert(i < nConstArraySize);
            uint64_t write_value_ = cval;
            std::string write_value = to_hex(write_value_);
            std::string addr = to_hex(baddr + i*byte_width);
            ret += "WRITE_UINT32(" + addr + "," + write_value + ");\n";
        }


        // we need the index reg number
        std::string write_value = to_hex(constArray.index_reg_num);
        std::string addr = to_hex(baddr + byte_width*nConstArraySize);
        ret += "WRITE_UINT8(" + addr + "," + write_value + ");";
        return ret;
    }

    void DoConstArrayWrite(uint64_t baseAddress, ConstArray& constArray, uint32_t byte_width)
    {
         printf("Const array offset 0x%x\n", GetConstArrayOffset(byte_width));
        uint64_t baddr = baseAddress + GetConstArrayOffset(byte_width);// + constArray.reg_num*(nConstArraySize*byte_width + 8);

        std::string ret;
        for (int i = 0; i < constArray.values.size(); i++)
        {
            auto& cval = constArray.values[i];
            assert(i < nConstArraySize);
            uint64_t write_value_ = cval;
            uint64_t addr = baddr + i*byte_width;
            printf("ConstArrayWrite 0x%llx, 0x%x\n", addr, write_value_);
            WRITE_UINT32(addr, write_value_);
        }


        // we need the index reg number
        uint64_t addr = baddr + byte_width*nConstArraySize;
        printf("ConstArray IndexSel 0x%x value %d\n", GetConstArrayOffset(byte_width)+byte_width*nConstArraySize, constArray.index_reg_num);
        WRITE_UINT8(addr, static_cast<uint8_t>(constArray.index_reg_num));
    }



    void DoControlWrite(uint64_t baseAddress, int numOutStatement, int layer, int inRegNumber, int outRegNumber)
    {
        
        if (outRegNumber == 255 || inRegNumber == 255) // added this --> fixed the array issue
            return;
        assert(outRegNumber < __UINT8_MAX__);

        unsigned int layerByteOffset = layer * bytesLayer;
        unsigned int cellByteOffset = inRegNumber * bytesCell;
        unsigned int outStatementOffset = numOutStatement * bytesOutStatement;

         auto hash_str = std::to_string(baseAddress) + "_" +
           std::to_string(layerByteOffset) + "_" +
           std::to_string(cellByteOffset) + "_" +
           std::to_string(outStatementOffset);
        auto idx_str = std::to_string(layer) + "_" + std::to_string(outRegNumber);

        int cell_index = VarOutMap[hash_str];
        
        uint64_t offset = layerByteOffset + cellByteOffset + outStatementOffset + cell_index;
        printf("DoControlWrite() 0x%x +0x%x\n", baseAddress, offset);
        VarOutMap[hash_str]++;
        //std::cout << hash_str << "\n";
        
        int routingIdx = IdxOutMap[idx_str];
        IdxOutMap[idx_str]++;

        assert(VarOutMap[hash_str] <= bytesCell); // this maps to maxVarOut
        assert(IdxOutMap[idx_str] <= bytesCell); 


        unsigned char write_val = static_cast<unsigned char>(outRegNumber);
        write_val |= (routingIdx << idxBit);
        printf("controlWrite  [layer %d] %d->%d idx(%d) idxbit=%d\n", layer, inRegNumber, outRegNumber, routingIdx, idxBit);

        WRITE_UINT8(baseAddress+offset, write_val);
    }

    std::string PrintControlWrite(uint64_t baseAddress, int numOutStatement, int layer, int inRegNumber, int outRegNumber)
    {
        if (outRegNumber == 255 || inRegNumber == 255) // added this --> fixed the array issue
            return "";
        
        

        unsigned int layerByteOffset = layer * bytesLayer;
        unsigned int cellByteOffset = inRegNumber * bytesCell;
        unsigned int outStatementOffset = numOutStatement * bytesOutStatement;

        assert(outRegNumber < __UINT8_MAX__);
        auto hash_str = std::to_string(baseAddress) + "_" +
           std::to_string(layerByteOffset) + "_" +
           std::to_string(cellByteOffset) + "_" +
           std::to_string(outStatementOffset);

        auto idx_str = std::to_string(layer) + "_" + std::to_string(outRegNumber);
        int cell_index = VarOutMap[hash_str];
        uint64_t offset = layerByteOffset + cellByteOffset + outStatementOffset + cell_index;
        std::string addr = to_hex(baseAddress + offset);
        VarOutMap[hash_str]++;

        int routingIdx = IdxOutMap[idx_str];
        IdxOutMap[idx_str]++;
        assert(VarOutMap[hash_str] <= bytesCell); // this maps to maxVarOut
        assert(IdxOutMap[idx_str] <= bytesCell); 


        unsigned char write_val = static_cast<unsigned char>(outRegNumber);
        write_val |= (routingIdx << idxBit);

        //printf("0x%x, 0x%x, 0x%x, 0x%x\n", layerByteOffset, cellByteOffset, outStatementOffset, cell_index);
        //printf("0x%x nOut %d, layer %d, inReg %d, outReg %d 0x%x\n", baseAddress, numOutStatement, layer, inRegNumber, outRegNumber, offset);
        std::string write_value = std::to_string(static_cast<unsigned char>(write_val));
        printf("controlWrite  [layer %d] %d->%d idx(%d) idxbit=%d\n", layer, inRegNumber, outRegNumber, routingIdx, idxBit);
        return "WRITE_UINT8(" + addr + ", " + write_value + ");\n";  
    }

    std::unordered_map<std::string, int> VarOutMap;
    std::unordered_map<std::string, int> IdxOutMap;



    bool CheckMeetHardwareConstaints(DTLResources* rsrc) const
    {
        bool ret = true;
        for (int i  =  0; i <= nLayers; i++)
        {
            ret = (rsrc->AddUnitsNeededLayer(i) <= GetLayerAddUnits(i));
            if (!ret) {
                printf("(Layer %d) %d <= %d\n", i, rsrc->AddUnitsNeededLayer(i), GetLayerAddUnits(i));
                std::cerr << "(rsrc->nAddNeeded <= nLayerAddUnits)\n"; goto end;
            }
            ret = (rsrc->MultUnitsNeededLayer(i) <= GetLayerMultUnits(i));
            if (!ret) {
                printf("(Layer %d) %d <= %d\n", i, rsrc->MultUnitsNeededLayer(i), GetLayerMultUnits(i));
                std::cerr << "(rsrc->nMultNeeded <= nLayerMultUnits)\n"; goto end;
            }

            ret = (rsrc->SubUnitsNeededLayer(i) <= GetLayerSubUnits(i));
            if (!ret) {
                printf("(Layer %d) %d <= %d\n", i, rsrc->SubUnitsNeededLayer(i), GetLayerSubUnits(i));
                std::cerr << "(rsrc->nSubNeeded <= nLayerSubUnits)\n"; goto end;
            }

            ret = (rsrc->ForLoopsNeeded <= nForLoopRegisters);
            if (!ret) {
                printf("%d <= %d\n", rsrc->ForLoopsNeeded, nForLoopRegisters);
                std::cerr << "(rsrc->ForLoopsNeeded <= nForLoopRegisters)\n"; goto end;
            }
            ret = (rsrc->nConstsNeeded <= nConstRegisters);
            if (!ret) {
                printf("%d <= %d\n", rsrc->nConstsNeeded, nConstRegisters);
                std::cerr << "(rsrc->nConstsNeeded <= nConstRegisters)\n"; goto end;
            }

            /*
                Our current convention is to use the last layer to route PassThru0 to the output,
                so we need an extra layer to do this successfully. We can probably do this in a better way
                later on
            */
            ret = (rsrc->nLayersNeeded + 1 <= nLayers);
            if (!ret) {
                printf("%d <= %d\n", rsrc->nLayersNeeded+1, nLayers);
                std::cerr << "(rsrc->nLayersNeeded <= nLayers)\n"; goto end;
            }
            ret = (rsrc->PassThruUnitsNeededLayer(i) <= GetLayerPassThruUnits(i)); 
            if (!ret) {
                printf("(Layer %d) %d <= %d\n", i, rsrc->PassThruUnitsNeededLayer(i), GetLayerPassThruUnits(i));
                std::cerr << "(rsrc->nPassThrough <= nLayerPassThrough)\n"; goto end;
            }
            ret = (rsrc->nOutStatements <= nOutStatements);
            if (!ret) {
                printf("%d <= %d\n", rsrc->nOutStatements, nOutStatements);
                std::cerr << "(rsrc->nOutStatements <= nOutStatements)\n"; goto end;
            }
            
            ret = (rsrc->nConstArrayNeeded <= nConstArray);
            if (!ret) {
                printf("%d <= %d\n", rsrc->nConstArrayNeeded, nConstArray);
                std::cerr << "(rsrc->nConstArrayNeeded <= nConstArrays)\n"; goto end;
            }

            ret = (rsrc->nConstArraySizeNeeded <= nConstArraySize);
            if (!ret) {
                printf("%d <= %d\n", rsrc->nConstArraySizeNeeded , nConstArraySize);
                std::cerr << "(rsrc->nConstArraySizeNeeded  <= nConstArraySize)\n"; goto end;
            }
        }
        

    end:
        return ret;
    }


    int GetTotalFuncUnits(LayerConfig cfg) const
    {
        return cfg.nAdd + cfg.nMult + cfg.nPassThru + cfg.nSub;
    }

    int GetTotalFuncUnitsLayer(int layer) const
    {
        assert(layer >= 0 && layer < layerCfgs.size());
        return GetTotalFuncUnits(layerCfgs[layer]);
    }

    int GetLayerAddUnits(int layer) const
    {
        assert(layer >= 0 && layer < layerCfgs.size());
        return layerCfgs[layer].nAdd;
    }

    int GetLayerMultUnits(int layer) const
    {
        assert(layer >= 0 && layer < layerCfgs.size());
        return layerCfgs[layer].nMult;
    }

    int GetLayerPassThruUnits(int layer) const
    {
        assert(layer >= 0 && layer < layerCfgs.size());
        return layerCfgs[layer].nPassThru;
    }

    int GetLayerSubUnits(int layer) const
    {
        assert(layer >= 0 && layer < layerCfgs.size());
        return layerCfgs[layer].nSub;
    }

    int GetMaxFuncUnits() const 
    {
        int ret = nForLoopRegisters + nConstRegisters + nConstArray;
        for (auto& layer: layerCfgs)
        {
            ret = std::max(ret, GetTotalFuncUnits(layer));
        }
        return ret;
    }



    int idxBit; // routing idx
    int bytesMagic;
    int bytesCell;
    int bytesLayer;
    int bytesOutStatement;
    int totalConfigRegionBits;
    int bits_outStatement;

    std::vector<LayerConfig> layerCfgs;
    int nLayers;
    int nConstRegisters;
    int nConstArray;
    int nConstArraySize;
    int nForLoopRegisters;
    int nOutStatements;
    int nMaxConfigs;

};





class FuncUnit
{
public:

    /*
        Used for passthrough
    */
    FuncUnit(int regAssignment, int inputA) : RegAssignment(regAssignment), InputA(inputA), InputB(255)
    {

    }

    FuncUnit(int regAssignment, int inputA, int inputB) : RegAssignment(regAssignment), InputA(inputA), InputB(inputB)
    {

    }

    ~FuncUnit()
    {

    }

    virtual std::string toString(int layer) = 0;
    int RegAssignment;
    int InputA;
    int InputB;
private:



};



class AddUnit : public FuncUnit
{
public:
    AddUnit(int regAssignment, int inputA, int inputB) : FuncUnit(regAssignment, inputA, inputB)
    {

    }

    ~AddUnit()
    {

    }

    virtual std::string toString(int layer) override;

};


class PassThrough : public FuncUnit
{
public:
    PassThrough(int regAssignment, int inputA) : FuncUnit(regAssignment, inputA)
    {

    }

    ~PassThrough()
    {
        
    }

    virtual std::string toString(int layer) override;
private:

};


class MultUnit : public FuncUnit
{
public:
    MultUnit(int regAssignment, int inputA, int inputB) : FuncUnit(regAssignment, inputA, inputB)
    {

    }

    ~MultUnit()
    {
        
    }

    virtual std::string toString(int layer) override;
};

class SubUnit : public FuncUnit
{
public:
    SubUnit(int regAssignment, int inputA, int inputB) : FuncUnit(regAssignment, inputA, inputB)
    {

    }

    ~SubUnit()
    {
        
    }

    virtual std::string toString(int layer) override;
};





class AGULayer
{
public:
    AGULayer(int nAddUnits, int nMultUnits, int nPassThru, int nSubUnits) : maxAddUnit(nAddUnits), maxMultUnit(nMultUnits), maxPassThrough(nPassThru), maxSubUnit(nSubUnits), \
        usedPassThrough(0), usedAddUnit(0), usedMultUnit(0), usedSubUnit(0)
    {
    }

    ~AGULayer()
    {

    }


    int MapPassThrough(PassThrough* unit)
    {
        int mapping = usedPassThrough;
        usedPassThrough++;
        printf("maxPassThrough %d, usedPassThrough %d\n", maxPassThrough, usedPassThrough);
        assert(usedPassThrough <= maxPassThrough);
        MapFuncUnit(unit);
        return maxAddUnit + maxMultUnit + mapping;
    }


     int MapSubUnit(SubUnit* unit)
    {
        int mapping = usedSubUnit;
        usedSubUnit++;
        assert(usedSubUnit <= maxSubUnit);
        MapFuncUnit(unit);
        return maxAddUnit + maxMultUnit +  maxPassThrough + mapping;
    }



    int MapAddUnit(AddUnit* unit)
    {
        int mapping = usedAddUnit;
        usedAddUnit++;
        assert(usedAddUnit <= maxAddUnit);
        MapFuncUnit(unit);
        return mapping;
    }


    int MapMultUnit(MultUnit* unit)
    {
        int mapping = usedMultUnit;
        usedMultUnit++;
        assert(usedMultUnit <= maxMultUnit);
        MapFuncUnit(unit);
        return maxAddUnit + mapping;
    }

    void MapFuncUnit(FuncUnit* unit)
    {
        inputRouting.push_back(unit);
    }


    int getNextAddUnit() const
    {
        return usedAddUnit;
    }

    int getNextMultUnit() const
    {
        return maxAddUnit+ usedMultUnit;
    }

    int getNextPassThrough() const
    {
        return maxAddUnit + maxMultUnit + usedPassThrough;
    }

    int getNextSubUnit() const
    {
        return maxAddUnit + maxMultUnit + maxPassThrough + usedSubUnit;
    }

    std::vector<FuncUnit*> inputRouting;

    std::string PrintControlWrites(uint64_t baseaddr, int numOutStmt, int layer, AGUHardwareStat* hwstat);
    void DoControlWrites(uint64_t baseaddr, int numOutStmt, int layer, AGUHardwareStat* hwstat);

    std::string PrintDigraph(int layer) const;
private:
    int maxAddUnit;
    int maxMultUnit;
    int maxPassThrough;
    int maxSubUnit;
    int usedAddUnit;
    int usedMultUnit;
    int usedPassThrough;
    int usedSubUnit;
};


/*
    We will add method onto this such that if we need less layers
    than the actual number of layers, then we just pass the finished
    value through to the end
*/
class OutStmtRouting
{
public:
    OutStmtRouting(int nLayers, AGUHardwareStat* hwStat, int usedLayers) : LayerCount(nLayers), hwStat(hwStat), UsedLayers(usedLayers)
    {
        
    }

    ~OutStmtRouting()
    {

    }


    bool PrintDigraph(const std::string& file);


    
    void CreateLayerIfNeeded(int layer)
    {
        auto it = LayerRouting.find(layer);
        if (it == LayerRouting.end())
        {
            int LayerAddUnitCount       = hwStat->GetLayerAddUnits(UsedLayers-1-layer);
            int LayerMultUnitCount      = hwStat->GetLayerMultUnits(UsedLayers-1-layer);
            int LayerPassThruCount      = hwStat->GetLayerPassThruUnits(UsedLayers-1-layer);
            int LayerSubUnitCount       = hwStat->GetLayerSubUnits(UsedLayers-1-layer);
            printf("%d Layer %d,%d,%d,%d\n", layer, LayerAddUnitCount, LayerMultUnitCount, LayerPassThruCount, LayerSubUnitCount);
            LayerRouting.insert(std::make_pair(layer, new AGULayer(LayerAddUnitCount, LayerMultUnitCount, LayerPassThruCount, LayerSubUnitCount)));
        }

    }


    int RequestSubUnit(int layer, int inputMapA, int inputMapB)
    {
        assert(layer >= 0 && layer < LayerCount);
        CreateLayerIfNeeded(layer);
        auto& routing = LayerRouting[layer];
        return routing->MapSubUnit(new SubUnit(routing->getNextSubUnit(), inputMapA, inputMapB));
    }


    int RequestAddUnit(int layer, int inputMapA, int inputMapB)
    {
        assert(layer >= 0 && layer < LayerCount);
        CreateLayerIfNeeded(layer);
        auto& routing = LayerRouting[layer];
        return routing->MapAddUnit(new AddUnit(routing->getNextAddUnit(), inputMapA, inputMapB));
    }

    int RequestMultUnit(int layer,  int inputMapA, int inputMapB)
    {
        assert(layer >= 0 && layer < LayerCount);
        CreateLayerIfNeeded(layer);
        auto& routing = LayerRouting[layer];
        return routing->MapMultUnit(new MultUnit(routing->getNextMultUnit(), inputMapA, inputMapB));
    }

    int RequestPassThrough(int layer, int inputMapA)
    {
        assert(layer >= 0 && layer < LayerCount+1);
        CreateLayerIfNeeded(layer);
        auto& routing = LayerRouting[layer];
        return routing->MapPassThrough(new PassThrough(routing->getNextPassThrough(), inputMapA));
    }


    /*
        We may want to do this in a slightly different way such that the indexes are contiguous,
        rather than overlapping
    */
    int GetNodeFuncUnitMapping(ASTNode* node)
    {
        if (OpFuncUnitMapping.find(node) != OpFuncUnitMapping.end())
            return OpFuncUnitMapping[node].first; 
        return -1;
    }

    int GetNodeLayerMapping(ASTNode* node)
    {
        if (OpFuncUnitMapping.find(node) != OpFuncUnitMapping.end())
            return OpFuncUnitMapping[node].second; 
        return -1;
    }

    void MapNodeFuncUnit(ASTNode* node, int unit, int layer)
    {
        OpFuncUnitMapping.insert(std::make_pair(node, std::make_pair(unit, layer)));
    }


    void SetAnswer(ASTNode* node)
    {
        auto it = OpFuncUnitMapping.find(node);
        assert(it != OpFuncUnitMapping.end());
        int unit = it->second.first;
        int layer = it->second.second;
        /*
            The answer may or may not fit exactly onto the hardware. We may use less layers than there
            actually are, and if this is the case we need to map the answer to pass throughs for the unused layers
        */
        int nLayers = LayerRouting.size();
        std::map<int, AGULayer*> newLayerRouting;
        int m = 0;
        for (int i = nLayers-1; i >= 0; i--)
        {
            newLayerRouting[m] = LayerRouting[i];
            m++;
        }
        LayerRouting = newLayerRouting;
        while(m < LayerCount+1)
        {
            int LayerAddUnitCount       = hwStat->GetLayerAddUnits(m);
            int LayerMultUnitCount      = hwStat->GetLayerMultUnits(m);
            int LayerPassThruCount      = hwStat->GetLayerPassThruUnits(m);
            int LayerSubUnitCount       = hwStat->GetLayerSubUnits(m);

            LayerRouting[m] = new AGULayer(LayerAddUnitCount, LayerMultUnitCount, LayerPassThruCount, LayerSubUnitCount);
            int input = unit;
            unit = RequestPassThrough(m, unit);
            printf("layer %d, passthru %d--->%d\n", m, input, unit);
            m++;
        }
        
        //for (auto& e: LayerRouting)





    }
    
    std::string PrintDigraph(const std::string& file) const;
    std::string PrintControlWrites(uint64_t baseaddr, int numoutstatement) const;
    void DoControlWrites(uint64_t baseaddr, int numoutstatement) const;

private:
    std::unordered_map<ASTNode*, std::pair<int, int>> OpFuncUnitMapping;
    AGUHardwareStat* hwStat;

    // layer# -> AGULayer*
    std::map<int, AGULayer*> LayerRouting;
    //std::vector<AGULayer*> LayerRouting;
    int LayerCount;
    int UsedLayers;
};



class ResourceAllocation{
public:
	static ResourceAllocation* build(ResourceAnalysis* ra, AGUHardwareStat* hwStat, ConditionalInfo condInfo)
    {
		ResourceAllocation * resourceAlloc = new ResourceAllocation;
		if (!resourceAlloc) return nullptr;
        resourceAlloc->hwStat = hwStat;
        resourceAlloc->CondInfo = condInfo;

        if (!hwStat->CheckMeetHardwareConstaints(ra->GetResources()))
        {
            std::cerr << "Configuration uses too many hardware resources.\n";
            exit(-1);
        }




        
        /*
            We need to allocate layers inside of resourceAlloc.

            We currently have all the registers, both ForLoop and Constants
            being mapped to indexes. Inside of the OutStmtNode we need to map
            these starting from the bottom up. We then will generate intermediate values
            as we move back up the tree, and we need to do this all the way up.

        */

        resourceAlloc->rsrcAnalysis = ra;

        ra->ast->resourceAllocation(resourceAlloc, 0);
		resourceAlloc->CalculateForLoopMagicValues();

        
        //ra->ast->resourceAllocation(resourceAlloc);
        return resourceAlloc;
		//return resourceAnalysis->GetResources();
	}


    void CalculateForLoopMagicValues()
    {
        /*
            We traverse backwards, as the inner loops are placed at the end of this
        */

        uint32_t d = rsrcAnalysis->GetResources()->nOutStatements; // the first divisor is # of outstatements
        for (int i = loopRegisters.size()-1; i >= 0; i--)
        {
            auto& loopReg = loopRegisters[i];
            auto magicnums = magicu(d);
            loopReg.hwDivMagic.add_indicator = magicnums.add_indicator;
            loopReg.hwDivMagic.M = magicnums.M;
            loopReg.hwDivMagic.s = magicnums.s;
          //  printf("M %lu, S %lu, add_indicator %d inc_condition %d stride %lu\n", magicnums.M, magicnums.s, magicnums.add_indicator, loopReg.increment_condition, d);

            /*
                This is equivalent to computing the stride for each loop counter
                as seen in the dtu_stateless_algo
            */
            d *= loopReg.increment_condition;
        }


    }


	void AllocLoopRegister(int initVal, int maxVal)
    {
        // we map backwards
        loopRegisters.push_back({initVal, maxVal, (rsrcAnalysis->GetResources()->ForLoopsNeeded - 1 - (int)loopRegisters.size())});
    }

    void AllocConstArray(int constArrayNum, std::vector<uint32_t> values)
    {
        constArrayRegisters.push_back({values, constArrayNum, 0});
    }


    int GetForLoopRegOffset() const
    {
        return hwStat->nConstRegisters + hwStat->nConstArray; // each const array can give 1 input at a time
    }

    

    /*
        We now know which for loop register is mapped to this ID


        may need to check the routing of these
    */
    void MapForLoopReg(std::string idName)
    {
        auto forloopsneeded = rsrcAnalysis->GetResources()->ForLoopsNeeded;
        idForLoopRegMap[idName] =  GetForLoopRegOffset() + (forloopsneeded - loopRegisters.size()-1);
        ReverseidForLoopRegMap[GetForLoopRegOffset() + (forloopsneeded - loopRegisters.size()-1)] = idName;
        //printf("For Loop reg %s --> %d\n", idName.c_str(), (forloopsneeded - loopRegisters.size()-1));
    }

    int ForLoopIDToMapping(std::string idName)
    {
        auto it = idForLoopRegMap.find(idName);

        // should always be mapped

        assert(it != idForLoopRegMap.end());

        return it->second;
    }

    std::string ReverseForLoopIDToMapping(int forLoopRegNum)
    {
        auto it = ReverseidForLoopRegMap.find(forLoopRegNum);

        // should always be mapped

        assert(it != ReverseidForLoopRegMap.end());

        return it->second;
    }


    OutStmtRouting* GetCurrentOutStatement() const
    {
        assert(OutStatementRouting.size());
        return OutStatementRouting[OutStatementRouting.size()-1];
    }

    void NewOutStatement(int depth)
    {
        int layers =  depth;
        assert(OutStatementRouting.size() <= hwStat->nOutStatements);
        OutStatementRouting.push_back(new OutStmtRouting(hwStat->nLayers, hwStat, layers));
    }

    
    void MultUnit(int layer, ASTNode* multNode, ASTNode* fromA, ASTNode* fromB)
    {
        auto currentOut = GetCurrentOutStatement();

        int a = currentOut->GetNodeFuncUnitMapping(fromA);
        int b = currentOut->GetNodeFuncUnitMapping(fromB);
       
        /*
            This should never occur. All units should be mapped somewhere. 
        */
        assert(a != -1 && b != -1);
        int unit = currentOut->RequestMultUnit(layer, a, b);
        printf("[mult layer%d], a %d::%d, b %d::%d --> %d\n", layer, a, fromA->myTag, b, fromB->myTag, unit);
        currentOut->MapNodeFuncUnit(multNode, unit, layer);
    }


    void SubUnit(int layer, ASTNode* minusNode, ASTNode* fromA, ASTNode* fromB)
    {
        auto currentOut = GetCurrentOutStatement();

        int a = currentOut->GetNodeFuncUnitMapping(fromA);
        int b = currentOut->GetNodeFuncUnitMapping(fromB);

        
        /*
            This should never occur. All units should be mapped somewhere. 
        */
        assert(a != -1 && b != -1);

        int unit = currentOut->RequestSubUnit(layer, a, b);
        printf("[sub layer%d], a %d::%d, b %d::%d --> %d\n", layer, a, fromA->myTag, b, fromB->myTag, unit);
        currentOut->MapNodeFuncUnit(minusNode, unit, layer);
    }



    void AddUnit(int layer, ASTNode* plusNode, ASTNode* fromA, ASTNode* fromB)
    {
        auto currentOut = GetCurrentOutStatement();

        int a = currentOut->GetNodeFuncUnitMapping(fromA);
        int b = currentOut->GetNodeFuncUnitMapping(fromB);

        
        /*
            This should never occur. All units should be mapped somewhere. 
        */
        assert(a != -1 && b != -1);
        int unit = currentOut->RequestAddUnit(layer, a, b);
        printf("[add layer%d], a %d::%d, b %d::%d ---> %d\n", layer, a, fromA->myTag, b, fromB->myTag, unit);
        currentOut->MapNodeFuncUnit(plusNode, unit, layer);
    }

    void PassThru(int layer, ASTNode* plusNode, ASTNode* fromA)
    {
        auto currentOut = GetCurrentOutStatement();
        int a = currentOut->GetNodeFuncUnitMapping(fromA);
        
        /*
            This should never occur. All units should be mapped somewhere. 
        */
        assert(a != -1);
        int unit = currentOut->RequestPassThrough(layer, a);
        printf("[passthru layer%d] passthru a %d::%d ---> %d\n", layer, a, fromA->myTag, unit);
        currentOut->MapNodeFuncUnit(plusNode, unit, layer);
    }

    void SetAnswer(ASTNode* fromA)
    {
        auto currentOut = GetCurrentOutStatement();
        currentOut->SetAnswer(fromA);
    }


    void PrintDigraph(int outStatementNum, const std::string& file)
    {
        OutStatementRouting[outStatementNum]->PrintDigraph(file);
    }


    void PrintInitStateRegisters(const std::string& file, uint64_t baseaddr);
    void DoInitStateRegisters(uint64_t baseAddr);
    void DoControlWrites(uint64_t baseaddr);
    void PrintControlWrites(const std::string& file, uint64_t baseaddr);
    

    bool BindArrayIndex(int arrayReg, int ForLoopReg)
    {
        auto it = ArrayIndexBinding.find(arrayReg);
        if (it != ArrayIndexBinding.end())
        {
            printf("Error. Array is already bound to index.\n");
            return false;
        }


        // we set the value here. We should be fine with for loop here
        // as the number of constArrayRegisters will be 1-2
        for (auto& constArray: constArrayRegisters)
        {
            if (constArray.reg_num == arrayReg)
                constArray.index_reg_num = ForLoopReg;
        }

        ArrayIndexBinding[arrayReg] = ForLoopReg;
        return true;
    }



    AGUHardwareStat* hwStat;
    ConditionalInfo CondInfo;
    ResourceAnalysis* rsrcAnalysis;

private:

    // [OutStmtNode # -> [Layer # -> N]]
    std::vector<OutStmtRouting*> OutStatementRouting;
    std::unordered_map<int, int> ArrayIndexBinding;
    std::vector<ConstArray> constArrayRegisters;
    std::unordered_map<int, std::string> ReverseidForLoopRegMap;
    std::unordered_map<std::string, int> idForLoopRegMap;
    std::vector<LoopReg> loopRegisters;
	ResourceAllocation() 
	{

	}
};

}







#endif