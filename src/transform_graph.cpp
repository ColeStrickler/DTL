#include "transform_graph.hpp"


/*
    For now, kernel arguments can only be used as metadata

    Later we will add an explicit `Compose()` call, to target transformed objects as well
*/

DTL::TransformGraph::TransformGraph(std::vector<DTL::DTLKernelNode*> kernels, IDNode* active) : m_Kernels(kernels), m_ActiveKernel(active)
{
    for (auto& kernel : kernels)
        m_KernelIDMap.insert({kernel->GetIDString(), kernel}); // need these to trace dependency chain


    CreateTransformDependencyDAG();
    assert(AssertNoCycles());
    ReverseTopologicalSortNodes();



}

DTL::TransformGraph::~TransformGraph()
{
}


/*
    Besides just a DAG, currently we require a tree
*/
bool DTL::TransformGraph::AssertNoCycles()
{
    TransformGraphNode* active_node = GetActiveNode();

    std::unordered_set<TransformGraphNode*> cycle_check_set;
    std::queue<TransformGraphNode*> q;
    q.push(active_node);

    while (!q.empty())
    {
        int qsize = q.size();
        for (int i = 0; i < qsize; i++)
        {
            TransformGraphNode* curr = q.front();
            q.pop();
            if (cycle_check_set.count(curr)) // found a cycle
                return false; 

            cycle_check_set.insert(curr);
            for (auto& incoming: curr->m_EdgeIn)
                q.push(incoming);
        }
    }
    return true;
}

void DTL::TransformGraph::CreateTransformDependencyDAG()
{
    /*
        Create graph nodes for the dependency DAG

    */
    DTL::DTLKernelNode* active = GetActiveKernel();
    for (auto& kernel: m_Kernels)
    {
        TransformGraphNode* node = new TransformGraphNode;
        node->m_Kernel = kernel;
        std::vector<IDNode*> idArgs = kernel->GetArguments();
        m_NodeIDMap[kernel->GetIDString()] = node;
    }


    for (auto& kernel: m_Kernels)
    {
        if (m_NodeIDMap.find(kernel->GetIDString()) == m_NodeIDMap.end())
            assert(false); // should never happen
        TransformGraphNode* kernelNode = m_NodeIDMap.at(kernel->GetIDString());

        std::vector<DTL::IDNode*> idArgs = kernel->GetArguments();
        for (auto& idArg: idArgs)
        {
            std::string idString = idArg->getName();
            if (m_NodeIDMap.find(idString) == m_NodeIDMap.end())
                assert(false); // should never happen
            
            TransformGraphNode* incomingEdge = m_NodeIDMap.at(idString);

            kernelNode->m_EdgeIn.push_back(incomingEdge);
        }
    }
}


/*
    We are guaranteed to have a DAG by the time this is called

    There is no chance that we run into cycles at this point
*/
void DTL::TransformGraph::ReverseTopologicalSortNodes()
{
    std::vector<TransformGraphNode*> rtop_order;
    TransformGraphNode* active_node = GetActiveNode();
    ReverseTopSortHelper(rtop_order, active_node);
    m_ReverseTopologicalOrderGraph = std::move(rtop_order);
}

void DTL::TransformGraph::ReverseTopSortHelper(std::vector<TransformGraphNode*>& rtop_order, TransformGraphNode* curr)
{
    assert(curr != nullptr);

    // DFS, but we do not reverse -- giving reverse top sort order
    for (auto& incoming: curr->m_EdgeIn)
        ReverseTopSortHelper(rtop_order, incoming);
    
    rtop_order.push_back(curr);
}


DTL::DTLKernelNode *DTL::TransformGraph::GetActiveKernel()
{
    std::string activeKernelID = m_ActiveKernel->getName();
    DTL::DTLKernelNode* node = GetKernelNodeByID(activeKernelID);
    if (node)
        return node;
    assert(false); // a kernel must be active
}


/*
    returns nullptr on failure
*/
DTL::DTLKernelNode *DTL::TransformGraph::GetKernelNodeByID(const std::string &id)
{
    if (m_KernelIDMap.find(id) != m_KernelIDMap.end())
        return m_KernelIDMap.at(id);
    return nullptr;
}

std::vector<DTL::TransformGraphNode*>& DTL::TransformGraph::BeginReverseTopologicalOrder() {
    return m_ReverseTopologicalOrderGraph;
}

DTL::TransformGraphNode *DTL::TransformGraph::GetActiveNode()
{
    DTLKernelNode* active = GetActiveKernel();
    std::string active_kernel_id = active->GetIDString();
    assert(m_NodeIDMap.find(active_kernel_id) != m_NodeIDMap.end());
    TransformGraphNode* active_node = m_NodeIDMap.at(active_kernel_id);
    return active_node;
}

std::string DTL::TransformGraph::PrintDotGraph()
{
    std::string ret;

    ret += "digraph TransformGraph {\n";

    for (auto& node: m_NodeIDMap)
    {
        auto& node_name = node.first;
        auto& node_incoming = node.second->m_EdgeIn;

        ret += node_name + " [label=\"" + node_name + "\"];\n";
        for (auto& incoming: node_incoming)
        {
            std::string incoming_node_name = incoming->m_Kernel->GetIDString();

            ret += incoming_node_name + " -> " + node_name + ";\n";
        }

    }

    ret += "}\n";

    return ret;
}

