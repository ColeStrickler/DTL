#include "software_sim.hpp"

uint32_t DTL::OutStmtSimNode::BindCoordsAndRun(
    const std::unordered_map<std::string, uint32_t>& input_coords,
    const std::unordered_map<std::string, SimEnvironmentStore>& environment)
{
    auto env = environment;
    for (const auto& coord : input_coords)
    {
        SimEnvironmentStore value;
        value.m_StoreType = SIMSTORETYPE::INT;
        value.m_IntStore = coord.second;
        env.insert_or_assign(coord.first, std::move(value));
    }
    return m_MyExp->Evaluate(env);
}




uint32_t DTL::ExpressionSimNode::Evaluate(
    const std::unordered_map<std::string, SimEnvironmentStore>& environment)
{
    if ((m_Op == SIMNODEOP::ADD || m_Op == SIMNODEOP::MULT || m_Op == SIMNODEOP::SUB)
        && (!m_Left || !m_Right))
        throw std::logic_error("DTL simulator has an unsupported operand");
    switch(m_Op)
    {
        case SIMNODEOP::ADD:
        {
            uint32_t val1 = m_Left->Evaluate(environment);
            uint32_t val2 = m_Right->Evaluate(environment);
            return val1 + val2;
        }
        case SIMNODEOP::ARRAY:
        {
            const auto& index = environment.at(m_IndexID);
            if (index.m_StoreType != SIMSTORETYPE::INT)
                throw std::invalid_argument("DTL array index must be an integer: " + m_IndexID);
            const auto& source = environment.at(m_IDVar);
            if (source.m_StoreType == SIMSTORETYPE::ARRAY)
                return source.m_ArrayStore.at(index.m_IntStore);
            if (source.m_StoreType == SIMSTORETYPE::METADATA)
            {
                if (!source.m_MetadataStore.m_ReadElement)
                    throw std::logic_error("DTL metadata is not bound: " + m_IDVar);
                return source.m_MetadataStore.m_ReadElement(index.m_IntStore);
            }
            throw std::invalid_argument("DTL indexed value is not an array or metadata: " + m_IDVar);
        }
        case SIMNODEOP::ID:
        {
            const auto& value = environment.at(m_IDVar);
            if (value.m_StoreType != SIMSTORETYPE::INT)
                throw std::invalid_argument("DTL scalar value is not an integer: " + m_IDVar);
            return value.m_IntStore;
        }
        case SIMNODEOP::LITERAL:
        {
            return m_IntVal;
        }
        case SIMNODEOP::MULT:
        {
            uint32_t val1 = m_Left->Evaluate(environment);
            uint32_t val2 = m_Right->Evaluate(environment);
            return val1 * val2;
        }
        case SIMNODEOP::SUB:
        {
            uint32_t val1 = m_Left->Evaluate(environment);
            uint32_t val2 = m_Right->Evaluate(environment);
            return val1 - val2;
        }
        default:
        {
            throw std::logic_error("DTL simulator expression is not implemented");
        }
    }

}

void DTL::ProgramNode::SimViewPass(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore>& environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    for (auto& stmt: myStatements)
    {
        stmt->SimViewPass(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
    }
}

void DTL::ConstDeclNode::SimViewPass(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    std::string id = myID->getName();
    auto val = myVal->GetVal();
    SimEnvironmentStore store;
    store.m_StoreType = SIMSTORETYPE::INT;
    store.m_IntStore = val;
    environment.insert({id, store});
}

void DTL::ConstArrayDeclNode::SimViewPass(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    std::string id = myID->getName();
    std::vector<uint32_t> vals;
    for (auto& val: myVals)
    {
        vals.push_back(val->GetVal());
    }
    
    SimEnvironmentStore store;
    store.m_StoreType = SIMSTORETYPE::ARRAY;
    store.m_ArrayStore = std::move(vals);
    environment.insert({id, store});
}


void DTL::MetadataStreamDeclNode::SimViewPass(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    std::string id = myID->getName();
    uint32_t data_size = dataSize->GetVal();
    if (data_size != 1 && data_size != 2 && data_size != 4)
        throw std::invalid_argument("DTL simulator supports 1, 2, or 4-byte metadata");
    SimEnvironmentStore store;
    MetadataStore metadataStore;
    metadataStore.m_DataSizeBytes = data_size;
    metadataStore.m_ID = id;
    store.m_StoreType = SIMSTORETYPE::METADATA;
    store.m_MetadataStore = std::move(metadataStore);
    environment.insert({id, store});
}


DTL::OutStmtSimNode* DTL::OutStmtNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    auto exp = myExp->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
    if (!exp)
        throw std::logic_error("DTL simulator has an unsupported output expression");
    OutStmtSimNode* out = new OutStmtSimNode(exp);

    return out;
}


DTL::ExpressionSimNode *DTL::ArrayIndexNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    ExpressionSimNode* node = new ExpressionSimNode(SIMNODEOP::ARRAY, nullptr, nullptr);
    node->SetID(myID->getName());
    node->SetIndexID(myIndexVar->getName());

    return node;
}   


DTL::ExpressionSimNode *DTL::IDNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    
    ExpressionSimNode* node = new ExpressionSimNode(SIMNODEOP::ID, nullptr, nullptr);
    node->SetID(getName());
    return node;
}

DTL::ExpressionSimNode *DTL::IntLitNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    ExpressionSimNode* node = new ExpressionSimNode(SIMNODEOP::LITERAL, nullptr, nullptr);
    node->SetIntVal(GetVal());
    return node;
}

DTL::ExpressionSimNode *DTL::TimesNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    auto left = myExp1->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
    auto right = myExp2->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);

    ExpressionSimNode* node = new ExpressionSimNode(SIMNODEOP::MULT, left, right);
    return node;
}

DTL::ExpressionSimNode *DTL::MinusNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    auto left = myExp1->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
    auto right = myExp2->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);

    ExpressionSimNode* node = new ExpressionSimNode(SIMNODEOP::SUB, left, right);
    return node;
}

DTL::ExpressionSimNode *DTL::PlusNode::SimViewPass2(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    auto left = myExp1->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
    auto right = myExp2->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);

    ExpressionSimNode* node = new ExpressionSimNode(SIMNODEOP::ADD, left, right);
    return node;
}



void DTL::ForStmtNode::SimViewPass(std::vector<uint32_t> &LogicalDimensions, OutStmtSimNode **OutStmtNode, std::unordered_map<std::string, SimEnvironmentStore> &environment, std::unordered_map<std::string, uint8_t>& idToDimIndex)
{
    

    if (myStatements.size() > 1)
    {
        throw std::logic_error("DTL simulator multiple output statements are not implemented");
    }

    std::string var = GetInitVar();
    if (myInit->Collapse(nullptr) != 0 || myCondExp->getTag() != NODETAG::LESSNODE)
        throw std::invalid_argument("DTL simulator requires zero-based loops with a strict upper bound");
    int regMax = myCondExp->Collapse(nullptr);
    if (regMax <= 0)
        throw std::invalid_argument("DTL simulator requires a positive literal loop bound");
    if (LogicalDimensions.size() > std::numeric_limits<uint8_t>::max())
        throw std::length_error("DTL simulator has too many loop dimensions");
    idToDimIndex.insert({var, LogicalDimensions.size()});
    LogicalDimensions.push_back(regMax);

    for (auto& stmt: myStatements)
    {
        if (stmt->getTag() == NODETAG::OUTSTMTNODE)
        {
            auto outsimnode = static_cast<DTL::OutStmtNode*>(stmt)->SimViewPass2(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
            *OutStmtNode = outsimnode;
        }
        else
        {
            stmt->SimViewPass(LogicalDimensions, OutStmtNode, environment, idToDimIndex);
        }
    }
}
