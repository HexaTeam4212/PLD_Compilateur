
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"


/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccVisitor {
public:

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }
  
  /*virtual antlrcpp::Any visitAxiom1(ifccParser::Axiom1Context *ctx) override {
    return visitChildren(ctx);
  }*/

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    
    std::cout<<".text\n"
    ".globl	main\n"
    " main: \n"
    "# prologue \n"
    "  pushq %rbp # save %rbp on the stack \n"
    "  movq %rsp, %rbp  # define %rbp for the current function \n"
    
    "# body \n";
    //visit(ctx->bloc());
    int retval = visit(ctx->expr());
    std::cout<<"  movl	$"<<retval<<", %eax\n"
    
    "# epilogue \n"
    " popq %rbp  # restore %rbp from the stack \n"
    " ret  # return to the caller (here the shell) \n";
    
    return 0;
  }

  virtual antlrcpp::Any visitBloc(ifccParser::BlocContext *ctx) override {
    return visitChildren(ctx);
  }
 
 virtual antlrcpp::Any visitInstructions(ifccParser::InstructionsContext *ctx) override {
   return visitChildren(ctx);
 }
  
  
  virtual antlrcpp::Any visitInstruction(ifccParser::InstructionContext *ctx) override {
    return visitChildren(ctx);
  }
  
  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
    
    
    
    
    return 0;
  }
  
  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {
   
    
    
    
    return 0;
  }
  
  /*virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }*/
  
  virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override {
    //Recuperer index dans table des symboles pour avoir l'adresse memoire
    return 4 ;
  }
  
  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
    std::cout<<"visite const"<<std::endl;
    return(int) stoi (ctx->CONST()->getText());
  }
  


};

