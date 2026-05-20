#ifndef MLIR_LOWERING_HPP
#define MLIR_LOWERING_HPP

// MLIR
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Value.h"
#include "mlir/IR/Location.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"

// LLVM
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/SmallVector.h"


#include <unordered_map>

// AST
#include "ast.hpp"

int lowering_main(DTL::ProgramNode* prog);


const std::string SHADOW_ARRAY = "SHADOW_MEM_REGION";


class ASTMLIRLowerer {
public:
  ASTMLIRLowerer(mlir::MLIRContext &ctx, mlir::OpBuilder &b)
      : context(ctx), builder(b), m_TotalShadowRegionSize(1) {}



  void lowerDTLKernel(DTL::ProgramNode *block);
  void lowerConstDecl(DTL::DeclNode* decl_node);
  void lowerForLoop(DTL::ForStmtNode* for_stmt);


  void allocMemRefArray();
  int getMemRefArraySize(DTL::ForStmtNode* for_stmt);

  void lowerOutStatement(DTL::OutStmtNode* out_stmt);
  mlir::Value lowerExpr(DTL::ExpNode* exp);





private:
  int m_TotalShadowRegionSize;
  mlir::MLIRContext &context;
  mlir::OpBuilder &builder;
  std::unordered_map<std::string, mlir::Value> symbolTable;
};






#endif

