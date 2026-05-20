#include "lowering.hpp"










int lowering_main()
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
        mlir::memref::MemRefDialect>();


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


    //
    // 7. Lower AST → MLIR
    //
    ASTMLIRLowerer lowerer(
        context,
        builder);


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

void ASTMLIRLowerer::lowerForLoop(DTL::ForStmtNode *for_stmt)
{
    for_stmt->Collapse(nullptr); // ralloc* not actually used

    int initVal = for_stmt->GetRegInitValue();
    int maxVal = for_stmt->GetRegMaxValue();

    auto loc = builder.getUnknownLoc();
    auto init_op = builder.create<mlir::arith::ConstantIndexOp>(loc, initVal);
    auto bounds_op = builder.create<mlir::arith::ConstantIndexOp>(loc, maxVal);
    auto step_op = builder.create<mlir::arith::ConstantIndexOp>(loc, 1); // forced to 1
    auto loop = builder.create<mlir::scf::ForOp>(loc, init_op, bounds_op, step_op);
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
            case DTL::NODETAG::IFSTMTNODE:
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

void ASTMLIRLowerer::lowerOutStatement(DTL::OutStmtNode *out_stmt)
{
    lowerExpr(out_stmt->GetExp());
}

void ASTMLIRLowerer::lowerExpr(DTL::ExpNode *exp)
{
    printf("here\n");
}
