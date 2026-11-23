#ifndef DTU_SOFTWARE_SIM_HPP
#define DTU_SOFTWARE_SIM_HPP


#include "dtl_api.hpp"
#include "optimizations/optimization_passes.hpp"
#include <cstring>
#include <functional>
#include <limits>
#include <memory>
#include <stdexcept>


namespace DTL
{
enum SIMNODEOP
{
    NOP,
    MULT,
    ADD,
    SUB,
    ID,
    LITERAL,
    ARRAY,
};

class ExpressionSimNode
{
public:
    ExpressionSimNode(SIMNODEOP op, ExpressionSimNode* left, ExpressionSimNode* right) : 
        m_Op(op), m_Left(left), m_Right(right)
    {

    }
    ~ExpressionSimNode() { delete m_Left; delete m_Right; }


    uint32_t Evaluate(const std::unordered_map<std::string, SimEnvironmentStore>& environment);

    void SetIndexID(std::string id) {m_IndexID = id;};
    void SetID(std::string id) {m_IDVar = id;};
    void SetIntVal(uint32_t val) {m_IntVal = val;}
private:
    SIMNODEOP m_Op;
    ExpressionSimNode* m_Left;
    ExpressionSimNode* m_Right;

    // optional fields, will only be filled based on the type
    std::string m_IndexID;
    std::string m_IDVar;
    uint32_t m_IntVal;
};


class OutStmtSimNode
{
public:
    OutStmtSimNode(ExpressionSimNode* exp) : m_MyExp(exp)
    {

    }
    ~OutStmtSimNode() { delete m_MyExp; }


    uint32_t BindCoordsAndRun(const std::unordered_map<std::string, uint32_t>& input_coords,
                             const std::unordered_map<std::string, SimEnvironmentStore>& environment);
private:
    ExpressionSimNode* m_MyExp;

};


enum class SIMSTORETYPE
{
    ARRAY,
    INT,
    METADATA
};

struct MetadataStore
{
    uint32_t m_DataSizeBytes = 0;
    std::string m_ID;
    std::function<uint32_t(uint32_t)> m_ReadElement;
};


struct SimEnvironmentStore
{
    SIMSTORETYPE m_StoreType = SIMSTORETYPE::INT;
    std::vector<uint32_t> m_ArrayStore;
    uint32_t m_IntStore = 0;
    MetadataStore m_MetadataStore;
};




template <typename DataType>
class DTUSimulatedView
{
public:
    DTUSimulatedView() = default;
    DTUSimulatedView(const std::string& kernel);
    ~DTUSimulatedView() = default;
    DTUSimulatedView(const DTUSimulatedView&) = delete;
    DTUSimulatedView& operator=(const DTUSimulatedView&) = delete;

    void SwapBackingStore(void* new_store) {
        m_PositionalObjectStorage.reset(static_cast<DataType*>(new_store));
    }

    DataType* GetBackingRegion() { return m_PositionalObjectStorage.get(); }
    uint64_t GetBackingSize() const { return m_PositionalObjectSize; }
    unsigned char* GetMetadataRegion(const std::string& id) { return m_ExternalMetadataRegions.at(id).data(); }
    uint64_t GetMetadataRegionSize(const std::string& id) const { return m_ExternalMetadataRegions.at(id).size(); }
    DTUSimulatedView& GetDependency(const std::string& id) { return *m_Dependencies.at(id); }
    DTUSimulatedView& GetMetadataView(const std::string& id) { return *m_MetadataRegions.at(id); }

    // Metadata names are local stream names; indices count stream elements.
    uint32_t ReadMetadata(const std::string& id, uint32_t index) const
    {
        const auto& metadata = GetMetadataStore(id);
        if (!metadata.m_ReadElement)
            throw std::logic_error("DTL metadata is not bound: " + id);
        return metadata.m_ReadElement(index);
    }

    void WriteMetadata(const std::string& id, uint32_t index, uint32_t value)
    {
        const uint32_t width = GetMetadataStore(id).m_DataSizeBytes;
        if (width != 1 && width != 2 && width != 4)
            throw std::invalid_argument("DTL simulator supports 1, 2, or 4-byte metadata");
        if (width < 4 && value >= (uint32_t(1) << (8 * width)))
            throw std::out_of_range("DTL metadata value does not fit stream width: " + id);

        const auto child = m_MetadataRegions.find(id);
        if (child != m_MetadataRegions.end())
        {
            // Write through the child's logical mapping, just as reads do.
            DataType& element = (*child->second)[index];
            std::memcpy(&element, &value, width);
            return;
        }

        auto& buffer = m_ExternalMetadataRegions.at(id);
        const uint64_t offset = uint64_t(index) * width;
        if (offset > buffer.size() || width > buffer.size() - offset)
            throw std::out_of_range("DTL metadata access: " + id);
        for (uint32_t byte = 0; byte < width; ++byte)
            buffer[offset + byte] = static_cast<unsigned char>(value >> (8 * byte));
    }

    // Resolve a kernel by its DTL name, including descendants of a child view.
    // The returned reference remains valid while the active view is alive.
    DTUSimulatedView& GetKernel(const std::string& id)
    {
        if (auto* kernel = FindKernel(id))
            return *kernel;
        throw std::out_of_range("DTL kernel not found: " + id);
    }

    DataType& operator[](uint32_t index){
        uint64_t logical_address = uint64_t(index)*sizeof(DataType);
        std::vector<uint32_t> logical_coords = LogicalAddressToCoord(logical_address);
        std::unordered_map<std::string, uint32_t> input_coords;
        for (const auto& entry : idToDimIndex)
        {
            input_coords.emplace(entry.first, logical_coords.at(entry.second));
        }
        uint64_t PositionalOffset = sizeof(DataType)*uint64_t(m_OutStmt->BindCoordsAndRun(input_coords, environment));

        if (PositionalOffset > m_PositionalObjectSize ||
            sizeof(DataType) > m_PositionalObjectSize - PositionalOffset)
            throw std::out_of_range("DTL simulated backing access");
        return m_PositionalObjectStorage[PositionalOffset / sizeof(DataType)];
    }

private:
    std::vector<uint32_t> LogicalAddressToCoord(uint64_t logical_address);

    const MetadataStore& GetMetadataStore(const std::string& id) const
    {
        const auto& entry = environment.at(id);
        if (entry.m_StoreType != SIMSTORETYPE::METADATA)
            throw std::invalid_argument("DTL name is not a metadata stream: " + id);
        return entry.m_MetadataStore;
    }

    DTUSimulatedView* FindKernel(const std::string& id)
    {
        if (id == m_KernelID)
            return this;
        const auto owned = m_Dependencies.find(id);
        if (owned != m_Dependencies.end())
            return owned->second.get();
        for (const auto& metadata : m_MetadataRegions)
            if (auto* kernel = metadata.second->FindKernel(id))
                return kernel;
        return nullptr;
    }

    std::string m_KernelID;
    std::vector<uint32_t> LogicalDimensions;
    std::unordered_map<std::string, SimEnvironmentStore> environment; 
    std::unordered_map<std::string, uint8_t> idToDimIndex;
    // Metadata links borrow child views; the active view owns all dependencies.
    std::unordered_map<std::string, DTUSimulatedView*> m_MetadataRegions;
    std::unordered_map<std::string, std::unique_ptr<DTUSimulatedView>> m_Dependencies;
    std::unordered_map<std::string, std::vector<unsigned char>> m_ExternalMetadataRegions;
    std::vector<uint32_t> m_LogicalObjectDimensions;
    std::vector<uint64_t> m_LogicalDimensionStrides;
    uint64_t m_LogicalObjectSize = 0;
    uint64_t m_PositionalObjectSize = 0;
    std::unique_ptr<DataType[]> m_PositionalObjectStorage;
    std::unique_ptr<OutStmtSimNode> m_OutStmt;
};

template <typename DataType>
inline DTUSimulatedView<DataType>::DTUSimulatedView(const std::string &kernel)
{
    std::istringstream input(kernel);
    DTL::TransformGraph* graph = nullptr;
    DTL::Scanner scanner(&input);
	DTL::Parser parser(scanner, &graph);
    int err = parser.parse();
    std::unique_ptr<DTL::TransformGraph> graphOwner(graph);
	if (err != 0){ 
        throw std::runtime_error("DTL simulator parsing failed");
    }

    auto main_kernel = graph->GetActiveKernel();
    std::string active_kernel_name = main_kernel->GetIDString();

    for (auto& node: graph->BeginReverseTopologicalOrder())
    {
        auto prog = node->m_Kernel->GetProgram();
        std::unique_ptr<DTL::NameAnalysis> na(DTL::NameAnalysis::build(prog));
        if (na == nullptr) {
            throw std::runtime_error("DTL simulator name analysis failed");
        }
        std::unique_ptr<DTL::TypeAnalysis> ta(DTL::TypeAnalysis::build(na.get()));
        if (ta == nullptr) {
            throw std::runtime_error("DTL simulator type analysis failed");
        }

        // Resolve named constants and fold bounds before constructing the view.
        prog = static_cast<DTL::ProgramNode*>(
            DTL::DTLOptimizer::OptimizeStatic(prog, DTL::DTL_OPTLEVEL::OPTMAX));

        const std::string id = node->m_Kernel->GetIDString();
        DTUSimulatedView* simView = this;
        if (id != active_kernel_name)
        {
            auto child = std::make_unique<DTUSimulatedView>();
            simView = child.get();
            m_Dependencies.emplace(id, std::move(child));
        }
        simView->m_KernelID = id;

        OutStmtSimNode* outStmt = nullptr;
        prog->SimViewPass(simView->LogicalDimensions, &outStmt,
                          simView->environment, simView->idToDimIndex);
        simView->m_OutStmt.reset(outStmt);
        if (!outStmt)
            throw std::logic_error("DTL simulator requires a supported output expression");

        uint64_t stride = sizeof(DataType);
        simView->m_LogicalDimensionStrides.resize(simView->LogicalDimensions.size());
        for (size_t dim = simView->LogicalDimensions.size(); dim-- > 0;)
        {
            const uint32_t extent = simView->LogicalDimensions[dim];
            if (extent == 0)
                throw std::invalid_argument("DTL simulator requires positive loop extents");
            simView->m_LogicalDimensionStrides[dim] = stride;
            if (stride > std::numeric_limits<uint64_t>::max() / extent)
                throw std::length_error("DTL simulated logical region is too large");
            stride *= extent;
        }
        simView->m_LogicalObjectSize = stride;

        // Backing sizes are bytes. Round up storage without changing the declared size.
        const uint64_t bytes = node->m_Kernel->GetBackingPhysSize();
        const uint64_t count = bytes / sizeof(DataType) + (bytes % sizeof(DataType) != 0);
        if (count > std::numeric_limits<size_t>::max() / sizeof(DataType))
            throw std::length_error("DTL simulated backing region is too large");
        simView->m_PositionalObjectSize = bytes;
        simView->m_PositionalObjectStorage = std::make_unique<DataType[]>(count);

        prog->PreprocessArgs();
        for (const auto& dep : node->m_Kernel->GetNonDTURegionMetadataDependencies())
        {
            const uint64_t metadataBytes = std::get<1>(dep);
            if (metadataBytes > std::numeric_limits<size_t>::max())
                throw std::length_error("DTL simulated metadata region is too large");
            simView->m_ExternalMetadataRegions.emplace(
                std::get<0>(dep), std::vector<unsigned char>(metadataBytes, 0));
            const std::string metadataID = std::get<0>(dep);
            auto& metadata = simView->environment.at(metadataID).m_MetadataStore;
            const uint32_t width = metadata.m_DataSizeBytes;
            metadata.m_ReadElement = [simView, metadataID, width](uint32_t index) {
                const auto& buffer = simView->m_ExternalMetadataRegions.at(metadataID);
                const uint64_t offset = uint64_t(index) * width;
                if (offset > buffer.size() || width > buffer.size() - offset)
                    throw std::out_of_range("DTL metadata access: " + metadataID);
                // DTL targets use little-endian unsigned metadata values.
                uint32_t value = 0;
                for (uint32_t byte = 0; byte < width; ++byte)
                    value |= uint32_t(buffer[offset + byte]) << (8 * byte);
                return value;
            };
        }
        for (const auto& dep : node->m_Kernel->GetDTURegionMetadataDependencies())
        {
            simView->m_MetadataRegions.emplace(
                dep.m_MetadataID, m_Dependencies.at(dep.m_KernelID).get());
            auto* child = simView->m_MetadataRegions.at(dep.m_MetadataID);
            auto& metadata = simView->environment.at(dep.m_MetadataID).m_MetadataStore;
            if (metadata.m_DataSizeBytes != sizeof(DataType))
                throw std::invalid_argument("DTL nested metadata width must match the view element size");
            const uint32_t width = metadata.m_DataSizeBytes;
            metadata.m_ReadElement = [child, width](uint32_t index) {
                // Re-enter the child view, including its own coordinates and environment.
                const DataType& element = (*child)[index];
                uint32_t value = 0;
                std::memcpy(&value, &element, width);
                return value;
            };
        }
    }

}

/*
    L^{-1}
*/
template <typename DataType>
inline std::vector<uint32_t> DTUSimulatedView<DataType>::LogicalAddressToCoord(uint64_t logical_address)
{
    if (logical_address >= m_LogicalObjectSize)
        throw std::out_of_range("DTL simulated logical access");
    uint64_t addr = logical_address;
    std::vector<uint32_t> return_coords;

    // we start with S_{Dimension n} to S_{Dimension 1}
    for (auto& stride: m_LogicalDimensionStrides)
    {
        uint32_t x_i = addr / stride;
        addr = addr % stride;
        return_coords.push_back(x_i);
    }

    return return_coords;
}

class SimViewPass
{
public:
    template<typename T>
    static DTUSimulatedView<T>* Transform(DTL::ProgramNode* prog, uint8_t opt_flags)
    {

        std::vector<uint32_t> LogicalObjectDimensions;
        OutStmtSimNode* outStmt;
        std::unordered_map<std::string, SimEnvironmentStore> environment;
        std::unordered_map<std::string, uint8_t> idToDimIndex;

        return prog->SimViewPass(LogicalObjectDimensions, &outStmt, environment, idToDimIndex);
    }



private:
    SimViewPass()
    {

    }

};
}


#endif

