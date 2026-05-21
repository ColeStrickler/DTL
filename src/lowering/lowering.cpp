#include "lowering.hpp"










int lowering_main(DTL::ProgramNode* prog)
{
        //
    // 1. Register dialects
    //
    mlir::DialectRegistry registry;

    registry.insert<
        mlir::arith::ArithDialect,
        mlir::scf::SCFDialect,
        mlir::func::FuncDialect,
        mlir::memref::MemRefDialect>();


    //
    // 2. Create MLIR context
    //
    mlir::MLIRContext context(registry);

    // Explicitly load only what we need
    context.loadDialect<
        mlir::arith::ArithDialect,
        mlir::scf::SCFDialect,
        mlir::func::FuncDialect,
        mlir::memref::MemRefDialect,
        mlir::affine::AffineDialect>();


    //
    // 3. Create builder
    //
    mlir::OpBuilder builder(&context);

    auto loc = builder.getUnknownLoc();


    //
    // 4. Create module
    //
    auto module = mlir::ModuleOp::create(loc);

    builder.setInsertionPointToStart(
        module.getBody());


    //
    // 5. Create top-level function
    //
    auto functionType =
        builder.getFunctionType({}, {});

    auto function =
        builder.create<mlir::func::FuncOp>(
            loc,
            "kernel",
            functionType);

    auto *entryBlock =
        function.addEntryBlock();
        

    builder.setInsertionPointToStart(
        entryBlock);

    auto oldIP = builder.saveInsertionPoint();


    //
    // 7. Lower AST → MLIR
    //
    ASTMLIRLowerer lowerer(
        context,
        builder);

    lowerer.lowerDTLKernel(prog);
    builder.restoreInsertionPoint(oldIP);

    //
    // 8. Finish function
    //
    builder.create<mlir::func::ReturnOp>(
        loc);


    //
    // 9. Print generated MLIR
    //
    module.dump();

    return 0;
}

void ASTMLIRLowerer::lowerDTLKernel(DTL::ProgramNode *block)
{
    for (auto& stmt: block->GetStatements())
    {
        switch (stmt->getTag())
        {
            case DTL::NODETAG::CONSTDECLNODE:
            case DTL::NODETAG::CONSTARRAYDECLNODE:
            {
                lowerConstDecl(static_cast<DTL::DeclNode*>(stmt));
            }
            case DTL::NODETAG::FORSTMTNODE:
            {
                m_TotalShadowRegionSize = getMemRefArraySize(static_cast<DTL::ForStmtNode*>(stmt));
                allocMemRefArray();
                lowerForLoop(static_cast<DTL::ForStmtNode*>(stmt));
                break;
            }
            default:
            {
                printf("ASTMLIRLowerer::lowerDTLKernel() encountered unexpexted DTL::NODETAG %d.\n", stmt->getTag());
                exit(-1);
            }
        }
    }
}

void ASTMLIRLowerer::lowerConstDecl(DTL::DeclNode *decl_node)
{
    printf("lowerConstDecl\n");
}

void ASTMLIRLowerer::lowerForLoop(DTL::ForStmtNode *for_stmt)
{

    int initVal = for_stmt->GetRegInitValue();
    int maxVal = for_stmt->GetRegMaxValue();
    m_TotalShadowRegionSize *= maxVal; // we just calculate this on the fly

    auto loc = builder.getUnknownLoc();
    //auto init_op = builder.create<mlir::arith::ConstantIndexOp>(loc, initVal);
    //auto bounds_op = builder.create<mlir::arith::ConstantIndexOp>(loc, maxVal);
    //auto step_op = builder.create<mlir::arith::ConstantIndexOp>(loc, 1); // forced to 1
    auto loop = builder.create<mlir::affine::AffineForOp>(loc, initVal, maxVal, 1);
    mlir::Value iv = loop.getInductionVar();

    symbolTable[for_stmt->GetInitVar()] = iv;
    auto oldIP = builder.saveInsertionPoint();
    builder.setInsertionPointToStart(loop.getBody()); // Change where we will put next loop


    const auto& statements = for_stmt->GetStatements(); // read only reference

    for (auto& stmt: statements)
    {
        switch (stmt->getTag())
        {
            case DTL::NODETAG::OUTSTMTNODE: lowerOutStatement(static_cast<DTL::OutStmtNode*>(stmt)); break;
            case DTL::NODETAG::FORSTMTNODE: lowerForLoop(static_cast<DTL::ForStmtNode*>(stmt)); break;
            case DTL::NODETAG::IFSTMTNODE:{printf("found ifstmt!\n");}
            case DTL::NODETAG::SWITCHSTMTNODE:
            {
                printf("Conditionals to MLIR not yet implemented!\n");
                exit(-1);
            }
            default:
            {
                printf("ASTMLIRLowerer::lowerForLoop() encountered unknown DTL::NODETAG in child statement %d.\n", stmt->getTag());
                exit(-1);
            }

        }
    }


}

void ASTMLIRLowerer::allocMemRefArray()
{
    auto loc = builder.getUnknownLoc();
    auto memrefType = mlir::MemRefType::get(
        {m_TotalShadowRegionSize},             // shape (e.g. array size)
        builder.getI32Type()                   // element type
    );

    auto alloc = builder.create<mlir::memref::AllocOp>(
        loc,
        memrefType
    );

    symbolTable[SHADOW_ARRAY] = alloc;
    return;
}

int ASTMLIRLowerer::getMemRefArraySize(DTL::ForStmtNode *for_stmt)
{
    for_stmt->Collapse(nullptr); // ralloc* not actually used
    int ret = for_stmt->GetRegMaxValue();

    auto children = for_stmt->GetStatements();
    if (children.size() == 1 && children[0]->getTag() == DTL::NODETAG::FORSTMTNODE)
        ret *= getMemRefArraySize(static_cast<DTL::ForStmtNode*>(children[0]));   

    return ret;
}

void ASTMLIRLowerer::lowerOutStatement(DTL::OutStmtNode *out_stmt)
{
    auto loc = builder.getUnknownLoc();
    mlir::Value exp_val = lowerExpr(out_stmt->GetExp());
    mlir::Value arr = symbolTable[SHADOW_ARRAY];

    auto load = builder.create<mlir::memref::LoadOp>(
        loc,
        arr,           // memref
        exp_val        // index (can be one or more values)
    );
    return;
}

mlir::Value ASTMLIRLowerer::lowerExpr(DTL::ExpNode *exp)
{
    auto loc = builder.getUnknownLoc();
    switch(exp->getTag())
    {
        case DTL::NODETAG::ARRAYINDEXNODE:
        {
            printf("ASTMLIRLowerer::lowerExpr() ARRAYINDEXNODE not yet implemented.\n");
            exit(-1);
        }
        case DTL::NODETAG::IDNODE:
        {
            auto idnode = static_cast<DTL::IDNode*>(exp);
            auto it = symbolTable.find(idnode->getName());
            assert(it != symbolTable.end());
            mlir::Value id_val = it->second;
            return id_val;
        }
        case DTL::NODETAG::INTLITNODE:
        {
            auto intnode = static_cast<DTL::IntLitNode*>(exp);
            mlir::Value intVal = builder.create<mlir::arith::ConstantIndexOp>(loc, intnode->GetVal());
            return intVal;
        }
        case DTL::NODETAG::MINUSNODE:
        {
            auto bnode = static_cast<DTL::BinaryExpNode*>(exp);
            mlir::Value val1 = lowerExpr(bnode->GetLeftChild());
            mlir::Value val2 = lowerExpr(bnode->GetRightChild());
            mlir::Value yieldVal = builder.create<mlir::arith::SubIOp>(loc, val1, val2);
            return yieldVal;
            break;
        }
        case DTL::NODETAG::PLUSNODE:
            {
            auto bnode = static_cast<DTL::BinaryExpNode*>(exp);
            mlir::Value val1 = lowerExpr(bnode->GetLeftChild());
            mlir::Value val2 = lowerExpr(bnode->GetRightChild());
            mlir::Value yieldVal = builder.create<mlir::arith::AddIOp>(loc, val1, val2);
            return yieldVal;
        }
        case DTL::NODETAG::TIMESNODE:
        {
            auto bnode = static_cast<DTL::BinaryExpNode*>(exp);
            mlir::Value val1 = lowerExpr(bnode->GetLeftChild());
            mlir::Value val2 = lowerExpr(bnode->GetRightChild());
            mlir::Value yieldVal = builder.create<mlir::arith::MulIOp>(loc, val1, val2);
            return yieldVal;
            break;
        }
        default:
        {
            printf("ASTMLIRLowerer::lowerExpr() encountered unexpected NODETAG %d.\n", exp->getTag());
            exit(-1);
        }
    }
}
