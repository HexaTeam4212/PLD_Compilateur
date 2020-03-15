
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


  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    
    std::cout<<".text\n"
    ".globl	main\n"
    " main: \n"
    "# prologue \n"
    "  pushq %rbp # save %rbp on the stack \n"
    "  movq %rsp, %rbp  # define %rbp for the current function \n"
    
    "# body \n";
    visit(ctx->bloc());
    std::string retval = visit(ctx->expr());
    std::cout<<"  movl	"<<retval<<", %eax\n"
    
    "# epilogue \n"
    " popq %rbp  # restore %rbp from the stack \n"
    " ret  # return to the caller (here the shell) \n";
    return 0;
  }

  virtual antlrcpp::Any visitBloc(ifccParser::BlocContext *ctx) override {
    std::cout<<"visite bloc"<<std::endl;
    return visitChildren(ctx);
  }
 
 virtual antlrcpp::Any visitInstructions(ifccParser::InstructionsContext *ctx) override {
   std::cout<<"visite instructions"<<std::endl;
   return visitChildren(ctx);
 }
  
  
 virtual antlrcpp::Any visitInstruction(ifccParser::InstructionContext *ctx) override {
    std::cout<<"visite instruction"<<std::endl;
    return visitChildren(ctx);
  }
  
  virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
    std::cout<<"visite declaration"<<std::endl;  
    //Ajout à la table de symboles ?
    return 0;
  }
  
  virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {
   std::cout<<"visite affectation"<<std::endl;
   std::string str_expr = visit(ctx->expr(1));
   std::string str_var = visit(ctx->expr(0));
   std::cout<<"movl "<<str_expr<<", "<<str_var<<std::endl;
    return 0;
  }

  
  virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override {
    std::cout<<"visite var"<<std::endl;
    //Recuperer index dans table des symboles pour avoir l'adresse memoire
    int val = 4;
    std::string str = "-"+std::to_string(val)+"(%rbp)";
    return str;
  }
  
  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
    std::cout<<"visite const"<<std::endl;
    int val = stoi (ctx->CONST()->getText());
    std::string str = "$"+std::to_string(val);
    
    return str;
  }
  


};

