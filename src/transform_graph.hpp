#ifndef DTL_TRANSFORM_GRAPH_HPP
#define DTL_TRANSFORM_GRAPH_HPP

#include <vector>
#include <queue>
#include <unordered_set>
#include "ast.hpp"


namespace DTL 
{
    

struct TransformGraphNode
{
    DTLKernelNode* m_Kernel;
    std::vector<TransformGraphNode*> m_EdgeIn;
};



/*
    We want to check if we can merge, if so we merge. If not, then each kernel goes in a separate config.

    We need these resources to be bound together in the DTLAPI such that they are freed and stored together.


    We can compile in reverse topological order, and then fix up the addresses right before mapping to the hardware, since 
    the shadow physical address is given at runtime

    If possible, we want to keep the compiling semantics of the old code in tact, and this more or less just instruments it
*/
class TransformGraph
{
public:
    TransformGraph(std::vector<DTLKernelNode*> kernels, IDNode* active);
    ~TransformGraph();
    bool AssertNoCycles();
    void CreateTransformDependencyDAG();
    void ReverseTopologicalSortNodes();
    DTLKernelNode* GetActiveKernel();
    DTLKernelNode* GetKernelNodeByID(const std::string& id);
    std::vector<TransformGraphNode*>& BeginReverseTopologicalOrder();
    TransformGraphNode* GetActiveNode();
    std::string PrintDotGraph();
private:
    void ReverseTopSortHelper(std::vector<TransformGraphNode*>& rtop_order, TransformGraphNode* curr);




    std::unordered_map<std::string, DTLKernelNode*> m_KernelIDMap;
    std::unordered_map<std::string, TransformGraphNode*> m_NodeIDMap;
    std::vector<DTLKernelNode*> m_Kernels;
    IDNode* m_ActiveKernel;
    std::vector<TransformGraphNode*> m_ReverseTopologicalOrderGraph;

};






};


#endif