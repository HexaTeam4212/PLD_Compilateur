#pragma once

#include <vector>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include "Program.h"
#include "Function.h"
#include "ReturnInstr.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "ExprVariable.h"
#include "Affectation.h"
#include "Declaration.h"
#include "Addition.h"

class Visitor : public ifccVisitor {

public:

      virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
            Program* program = new Program();

            //Fill program with children visit
            for(auto i : ctx->definitionFunction()) {
                  program->addFunction((Function*)visit(i));
            }

            return program;
      }

      virtual antlrcpp::Any visitDefinitionFunction(ifccParser::DefinitionFunctionContext *ctx) override {
            Function* function = new Function();
            function->setReturnType(visit(ctx->type()));
            function->setName(ctx->NAME()->getText());
            //to add in the future : parameters parsing

            //Handle instructions of functions
            std::vector<Instruction*> instructions;
            for(int i = 0; i < ctx->instr().size(); i++) {
                  instructions.push_back((Instruction*)visit(ctx->instr(i)));
            }
            function->setInstructions(instructions);

            return function;
      }

      virtual antlrcpp::Any visitReturn(ifccParser::ReturnContext *ctx) override {
            return (Instruction*) new ReturnInstr((Expression*)visit(ctx->expr()));
      }

      virtual antlrcpp::Any visitInteger(ifccParser::IntegerContext *ctx) override {
            return (std::string) ctx->INTEGER()->getText();
      }

      virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
            return (Expression*) new ExprConstante(ctx->CONST()->getText());
      }
 
      virtual antlrcpp::Any visitVar(ifccParser::VarContext *ctx) override {
            return (Expression*) new ExprVariable(ctx->VAR()->getText());
      }

      virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
            std::vector<ExprVariable*> varsDeclared;
            for(int i = 0; i < ctx->VAR().size(); i++) {
                  ExprVariable* newVar = new ExprVariable(ctx->VAR().at(i)->getText());
                  varsDeclared.push_back(newVar);
            }

            return (Instruction*) new Declaration(varsDeclared, visit(ctx->type()));
      }

      virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {
            std::string varName = ctx->VAR()->getText();
            Expression* expr = (Expression*) visit(ctx->expr());
            return (Instruction*) new Affectation(varName, expr);
      }

	  virtual antlrcpp::Any visitAddition(ifccParser::AdditionContext *ctx) override {
		  std::string varName = ctx->VAR()->getText();
		  std::vector<Expression*> exprAdded;
		  for (int i = 0; i < ctx->expr().size(); i++) {
			  Expression* oneExpr = (Expression*) visit(ctx->expr().at(i));
			  exprAdded.push_back(oneExpr);
		  }
		  return (Instruction*) new Addition(varName, exprAdded);
	  }

};