//
//  visitor.h
//  PLD-COMP
//
//  Created by H4212 on 02/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

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
#include "Multiplication.h"
#include "Soustraction.h"
#include "Division.h"
#include "Appel.h"

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
		  std::string returnType = visit(ctx->type(0));
		  std::string functionName =ctx->NAME(0)->getText();
		  //parameters parsing
		  std::vector<ExprVariable*> varArgument;
		  std::vector<std::string> varType;

		  for (int i = 1; i < ctx->NAME().size(); i++) {
			  ExprVariable* newArgument = new ExprVariable(ctx->NAME().at(i)->getText());
			  std::string type = visit(ctx->type().at(i));
			  varArgument.push_back(newArgument);
			  varType.push_back(type);
		  }
		  //Handle instructions of functions
		  Function* function = new Function(returnType, functionName, varArgument);
		  std::vector<Instruction*> instructions;
		  Instruction* argInstr = (Instruction*) new DeclarationArg(varArgument, varType);

		  instructions.push_back(argInstr);

		  for (int i = 0; i < ctx->instr().size(); i++) {
			  instructions.push_back((Instruction*)visit(ctx->instr(i)));
		  }
		  function->setInstructions(instructions); 
            return function;
      }
	  
	  virtual antlrcpp::Any visitCalling(ifccParser::CallingContext *ctx) override {
		  std::string functionName = ctx->NAME(0)->getText();
		  std::string varName =  ctx->NAME(1)->getText();
		  std::vector<ExprVariable*> varArgumentAppel;
		  for (int i = 1; i < ctx->NAME().size(); i++) {
			  ExprVariable* newArgument = new ExprVariable(ctx->NAME().at(i)->getText());
			  varArgumentAppel.push_back(newArgument);
		  }
		  return (Instruction*) new Appel(varName, functionName, varArgumentAppel);

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
            return (Expression*) new ExprVariable(ctx->NAME()->getText());
      }

      virtual antlrcpp::Any visitDeclaration(ifccParser::DeclarationContext *ctx) override {
            std::vector<ExprVariable*> varsDeclared;
            for(int i = 0; i < ctx->NAME().size(); i++) {
                  ExprVariable* newVar = new ExprVariable(ctx->NAME().at(i)->getText());
                  varsDeclared.push_back(newVar);
            }

            return (Instruction*) new Declaration(varsDeclared, visit(ctx->type()));
      }

      virtual antlrcpp::Any visitAffectation(ifccParser::AffectationContext *ctx) override {
            std::string varName = ctx->NAME()->getText();
            Expression* expr = (Expression*) visit(ctx->expr());
            return (Instruction*) new Affectation(varName, expr);
      }

	virtual antlrcpp::Any visitAddition(ifccParser::AdditionContext *ctx) override {
		Expression* exprGAdded;
		Expression* exprRAdded;
		  
		exprGAdded = (Expression*) visit(ctx->expr(0));
		exprRAdded = (Expression*) visit(ctx->expr(1));

		return (Expression*) new Addition(exprGAdded,exprRAdded);
	}


	virtual antlrcpp::Any visitMultiplication(ifccParser::MultiplicationContext *ctx) override {
		Expression* exprGMult;
		Expression* exprRMult;

		exprGMult = (Expression*)visit(ctx->exprLvl2(0));
		exprRMult = (Expression*)visit(ctx->exprLvl2(1));

		return (Expression*) new Multiplication(exprGMult, exprRMult);
	}

	virtual antlrcpp::Any visitSoustraction(ifccParser::SoustractionContext *ctx) override {
		Expression* exprGDiff;
		Expression* exprRDiff;

		exprGDiff = (Expression*)visit(ctx->exprLvl1(0));
		exprRDiff = (Expression*)visit(ctx->exprLvl1(1));

		return (Expression*) new Soustraction(exprGDiff, exprRDiff);
	}

	virtual antlrcpp::Any visitDivision(ifccParser::DivisionContext *ctx) override {
		Expression* exprGDiv;
		Expression* exprRDiv;

		exprGDiv = (Expression*)visit(ctx->exprLvl2(0));
		exprRDiv = (Expression*)visit(ctx->exprLvl2(1));

		return (Expression*) new Division(exprGDiv, exprRDiv);
	}
	virtual antlrcpp::Any visitCasStandardLvl1(ifccParser::CasStandardLvl1Context *ctx) override {
		return (Expression*)visit(ctx->exprLvl1());
	}
      virtual antlrcpp::Any visitCasStandardLvl2(ifccParser::CasStandardLvl2Context *ctx) override {
            return (Expression*)visit(ctx->exprLvl2());
      }

      virtual antlrcpp::Any visitParenthese(ifccParser::ParentheseContext *ctx) override {
            return (Expression*)visit(ctx->expr());
      }
};