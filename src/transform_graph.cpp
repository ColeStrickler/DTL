#include "transform_graph.hpp"




DTL::TransformGraph::TransformGraph(std::vector<DTL::DTLKernelNode*> kernels, IDNode* active) : m_Kernels(kernels), m_ActiveKernel(active)
{
    for (auto& kernel : kernels)
        m_KernelIDMap.insert({kernel->GetIDString(), kernel}); // need these to trace dependency chain


    CreateTransformDependencyDAG();
}

DTL::TransformGraph::~TransformGraph()
{
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
