#ifndef DTL_API_HPP
#define DTL_API_HPP
#include "scanner.hpp"
#include "resource_alloc_pass.hpp"
#include "name_analysis.hpp"
#include "type_analysis.hpp"
#include "ast_transform_pass.hpp"
#include "util.hpp"

// System Headers
#include <fcntl.h> 
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <tuple>

#define Kilobyte            1024
#define Megabyte            Kilobyte*1024

namespace DTL
{
    


#define DEVICE_FILE "/dev/DTU-RUNTIME-DRIVER"
#define IOCTL_NEW_PA        _IO('a', 1)
#define IOCTL_REMAP_PA      _IO('a', 2)
typedef struct RemapPARequest
{
    void* u_VA;
    void* u_NewPA;
}RemapPARequest;



#define DTU_CONFIG_SIZE 0x1000
#define DTU_CONFIG_BASE 0x3000000ULL
#define AGU_CONFIG_BASE 0x4000000ULL
#define AGU_CONFIG_RST 0xf00

#define DTU_CONFIG_BASE_COLUMNWIDTH 0x40ULL
#define AGU_CONFIG_OFFSET(config) (config*0x1000)
#define DTU_REGION_ADDR 0x100000000ULL
#define DTU_REGION_SIZE 0x80000000ULL



// this is the only place we should have to update
#define UPDATE_CONFIG_PHYSMAP(base, config, maxConfigs, EphemeralConfigPhysStart) (WRITE_UINT64((uint64_t)base+(config*0x8)+(2*maxConfigs*0x8)+0x400, EphemeralConfigPhysStart))
#define UPDATE_CONFIG_SIZE(base, config, maxConfigs, size) (WRITE_UINT64(base+(config*0x8)+(maxConfigs*0x8)+0x400, size))
#define UPDATE_CONFIG_START(base, config, maxConfigs, size) (WRITE_UINT64(base+(config*0x8)+0x400, size))





enum DTL_API_ERROR
{
    NO_ERROR_OK,
    DEFAULT_ERROR,
    RESOURCES_INSUFFICIENT,
    COMPILE_ERROR_SCANNING,
    COMPILE_ERROR_PARSING,
    COMPILE_ERROR_NAME_ANALYSIS,
    COMPILE_ERROR_TYPE_ANALYSIS,
    COMPILE_ERROR_RESOURCE_ANALYSIS,
    COMPILE_ERROR_RESOURCE_ALLOCATION,
    COMPILE_ERROR_TRANSFORM_PASS,
};

enum DTL_KERNEL_DEPENDENCY
{
    METADATA,
    BASE_OBJECT
};


// Forward declaration
struct CompiledKernelDependency; 
struct CompiledNonDTUMetadata;
/*
    A compiled view is just a vector of ByteWrites

    Each ByteWrite configures an MMIO register in the DTU
*/
struct CompiledView
{
    CompiledView(std::string view_name, uint64_t base_object_size, uint64_t view_size, std::vector<ByteWrite>& bytewrites);
    ~CompiledView() = default;

    void DoByteWrites(std::unordered_map<std::string, uint64_t>& args, uint64_t baseAddr);
    uint64_t m_BaseObjectSize;      // Physical Address space needed
    uint64_t m_ViewSize;            // Virtual Address space needed
    std::vector<ByteWrite> m_ByteWrites;
    std::string m_ViewName;
    std::vector<CompiledKernelDependency> m_Dependencies;
    std::vector<CompiledNonDTUMetadata> m_NonDTURegionMetadata;
};

/*
    We can save this structure, and pass into MapOntoDTUHardware() later
    without having to recompile 
*/
struct CompiledDTLProgram
{
    CompiledDTLProgram();
    ~CompiledDTLProgram();

    uint8_t m_NeededConfigs = 0;
    DTL_API_ERROR m_Error = DTL_API_ERROR::NO_ERROR_OK;
    std::vector<CompiledView*> m_Views = {};
    std::string m_ActiveViewName;
};

class DTUResourceHandle;
class EphemeralRegion;
struct KernelDependency
{
    DTUResourceHandle* m_UpstreamDependency;
    DTL_KERNEL_DEPENDENCY m_DependencyType;
    uint8_t m_DependencyNumber;
};

struct CompiledKernelDependency
{
    CompiledView* m_DownstreamView;
    DTL_KERNEL_DEPENDENCY m_DependencyType;
    uint8_t m_DependencyNumber;
};

struct CompiledNonDTUMetadata
{
    std::string m_MetadataID;
    uint64_t m_MetadataRegionSize;
    uint8_t m_DependencyNumber;
};

/*
    MetadataRegion's allow controlling the metadata portion of a DTU kernel


    Upon compilation into a DTUResourceHandle, the MetadataRegion will do one of the following:
    1. if the metadataregion is another DTU kernel, we just need to ensure the pointers line up
    2. if the metadataregion is just pure array, we can allocate this region from the normal allocator
*/
struct MetadataRegion
{
    MetadataRegion() = default;
    ~MetadataRegion();
    // Basically, we want r/w pointers that are different if this is a 
    inline bool IsDTURegion() {return isDTURegion;};                // !isNormalMemoryRegion()
    inline bool isNormalMemoryRegion() {return !IsDTURegion();};    // !IsDTURegion()

    inline void* GetMetadataWriteRegion() const { return m_WriteRegion;}
    inline void* GetMetadataReadRegion() const {return m_ReadRegion;}
    bool isDTURegion;
    void* m_WriteRegion; // IsDTURegion() ? (!= m_ReadRegion) : (= m_ReadRegion)
    void* m_ReadRegion;
    uint64_t m_RegionSize;
    DTUResourceHandle* m_ResourceHandle; // corresponding resource handle
    //int m_MmapFD; used DTLAPI fd that is already allocated
};


class DTUResourceHandle
{
public:
    DTUResourceHandle() = default;
    ~DTUResourceHandle();
    std::string m_HandleName;
    std::unordered_map<std::string, MetadataRegion*> m_MetaDataRegions; 
    EphemeralRegion* m_MainRegion;
    std::unordered_map<std::string, DTUResourceHandle*> m_SubHandles; // get kernel by name
    std::vector<KernelDependency> m_DependencyOf; // Track all kernels that are dependent on this one
    uint64_t m_BaseObjectSize;      // Physical Address space needed
    uint64_t m_ViewSize;            // Virtual Address space needed

    inline void* GetReadRegion() const {return m_MainRegion->GetHeadlessReadRegion();};
    inline void* GetWriteRegion() const  {return m_MainRegion->GetHeadlessWriteregion();}
    uint64_t GetPositionalObjectSize() const {return m_BaseObjectSize;}
    uint64_t GetLogicalObjectSize() const {return m_ViewSize;}
    

    // If we sync the base object, we also have to sync the upstream objects as well
    // This may require either updating the metadata object or base object, depending
    // on what kind of dependency the object is
        
    void Sync();
    void SyncDependent(KernelDependency dep, std::tuple<uint64_t, uint64_t, uint64_t>& addrTriple);
    void AddDependencyOf(DTUResourceHandle* upstreamDependency, DTL_KERNEL_DEPENDENCY dependencyType, uint8_t dependencyNum);
};






class EphemeralRegion
{
public:
    EphemeralRegion(uint64_t positional_region_offset, uint64_t logical_region_size, int config_num, uint64_t physical_backing_start, AGUHardwareStat* hwStat, uint64_t agu_region_base, uint64_t positional_region_size);
    ~EphemeralRegion();
    EphemeralRegion* Clone(int new_config);
    /*
        We want methods for: access, delete, locking, update

        We want to enable access by index and by offset
    */

    // Maybe define some macros? not sure how we want to do this yet

    /*
        This method remaps the va->pa region and ensures that region pulls in latest data
    */


   /*
        We need to add methods to write to the uncached backing of these regions and
        to enable teardown

   
   */

    void SetDataSize(uint8_t size);
    int Sync(); //


    void UpdateBackingObjectAddr(uint64_t addr);
    void UpdateMetadataObjectAddr(uint8_t metadataObjectNumber, uint64_t addr);


    void* GetHeadlessReadRegion(); // get raw pointer to ephemeral region, no bounds checking, writes allowed
    void* GetHeadlessWriteregion();

    uint64_t GetRegionOffset() {return m_RegionOffset; }

    void GuardedWrite_8(uint64_t offset, uint8_t data);
    uint8_t GuardedRead_8(uint64_t offset);
    uint16_t GuardedRead_16(uint64_t offset);
    uint32_t GuardedRead_32(uint64_t offset);
    uint64_t GuardedRead_64(uint64_t offset);

    float GuardedRead_Float(uint64_t offset);

    inline int GetConfig() {return m_ConfigNum;}


    /*
        We return {virtual, shadow PA, positional PA}
    */
    inline std::tuple<uint64_t, uint64_t, uint64_t> GetAddrMappingTriple() 
    { return std::make_tuple(
        reinterpret_cast<uint64_t>(m_LogicalRegionAccess),
        m_CurrentEphemeralPhysicalAddr,
        m_PhysBackingStart + m_PositionalRegionOffset);
    }

private:
    uint64_t m_PositionalRegionOffset;
    uint64_t m_PhysBackingStart;
    uint64_t m_LogicalRegionSize;
    uint64_t m_PositionalRegionSize;
    uint64_t m_AGUControlRegionBase;
    int m_ConfigNum;
    void* m_LogicalRegionAccess;
    void* m_PositionalRegionAccess;
    int m_Regionfd;
    int m_Positionalfd;
    int m_DTURuntimeDriverfd;
    void* m_DTUConfigRegion;
    AGUHardwareStat* hwStat;
    
    uint64_t m_CurrentEphemeralPhysicalAddr;

    //int open_fd(const std::string& path);

    


};


class BuddyNode
{
public:
    BuddyNode(uint64_t TrackedSize, uint64_t TrackedOffset, BuddyNode* parent);
    ~BuddyNode();

    void Split();
    BuddyNode* GetLeft();
    BuddyNode* GetRight();
    void SetInUse();
    int SetFree();
    bool isFree();
    bool isRoot();
    void Coalesce();
    

    void DebugPrint();

    uint64_t GetTrackedOffset();
    uint64_t GetTrackedSize();

private:
    uint64_t m_TrackedOffset;
    uint64_t m_TrackedSize;
    int m_IsFree; // this is now an int, so we can make use of cloning, pointing multiple ephemeral regions to same place
    BuddyNode* m_LeftChild;
    BuddyNode* m_RightChild;
    BuddyNode* m_Parent;
};


#define BUDDY_ALLOC_FAILURE     UINT64_MAX
#define CONFIG_ALLOC_FAILURE    (UINT64_MAX-1ULL)


class BuddyAllocator
{
public:
    BuddyAllocator(uint64_t region_size);
    ~BuddyAllocator();
    void FreeNode(uint64_t offset);  
    uint64_t AllocNode(uint64_t size_needed);
    void FindAndIncNode(uint64_t offset);

    void DebugPrintTree();



    
private:
    uint64_t FindAndAllocFreeNode(uint64_t size_needed, BuddyNode* currentNode);
    BuddyNode* FindNode(uint64_t offset, BuddyNode* currNode);

    uint64_t m_Size;
    BuddyNode* m_RootNode;


};


class API
{
public:
    API(uint64_t realBackingStart = DTU_REGION_ADDR,
        uint64_t realBackingSize = DTU_REGION_SIZE); // if we allow automatically reading
    API(AGUHardwareStat* hwStat,
        uint64_t realBackingStart = DTU_REGION_ADDR,
        uint64_t realBackingSize = DTU_REGION_SIZE); // if we want to manually configure
    ~API();



    bool CheckHasAvailableResources(CompiledDTLProgram& dtlProg);
    DTUResourceHandle* MapTODTUHardware(CompiledDTLProgram& dtlProg);

    /*
        Should be a mmap'ed address being passed in
    */
    void SetAGUControlRegionBaseAddr(uint64_t newBaseAddr);
    void ReadHardwareInfo();
    bool CompileAndProgramHardware(const std::string& dtlProgram, EphemeralRegion* region);
    
    // Deprecated
    bool Compile(const std::string& dtlProgram);

    CompiledDTLProgram CompileProgram(const std::string& dtlProgram);
    bool ProgramHardware(EphemeralRegion* region);
    void ProgramHardwareByteWrites(EphemeralRegion* region, CompiledView* view, std::unordered_map<std::string, uint64_t>& args);

    void ResetConfig(int config);

    void DebugPrintAllocator();
    
    EphemeralRegion* AllocEphemeralRegion(uint64_t size_needed);
    EphemeralRegion* AllocEphemeralRegion(uint64_t positional_size_needed, uint64_t logical_size_needed);

    EphemeralRegion* CloneEphemeralRegion(EphemeralRegion* ephemeralRegion);
    void FreeEphemeralRegion(EphemeralRegion* ephemeralRegion);


    uint64_t GetError();
    AGUHardwareStat* GetHWStat();
private:
    uint64_t AllocateRegion(uint64_t size);
    MetadataRegion* GenMetadataRegion(CompiledNonDTUMetadata& metadataDep);


    int AllocateConfig();
    void FreeConfig(int config);
    void SetError(uint64_t Error);
    uint64_t m_ConfigBitmap; // config 
    uint64_t m_ReceivedPAFromDriver;
    uint64_t m_RealBackingStart;
    uint64_t m_RealBackingSize;
    BuddyAllocator* m_BuddyAllocator;
    AGUHardwareStat* hwStat;
    uint64_t AGUControlRegionBaseAddress; // will index off this
    DTL::ResourceAllocation* ralloc; // possibly move this to the ephemeral region? 


    int m_AGUControlRegionfd;

    uint64_t m_ErrorCode;
};




};








#endif
