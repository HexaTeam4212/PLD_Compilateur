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

		exprGDiff = (Expression*)visit(ctx->expr(0));
		exprRDiff = (Expression*)visit(ctx->expr(1));

		return (Expression*) new Soustraction(exprGDiff, exprRDiff);
	}

	virtual antlrcpp::Any visitDivision(ifccParser::DivisionContext *ctx) override {
		Expression* exprGDiv;
		Expression* exprRDiv;

		exprGDiv = (Expression*)visit(ctx->exprLvl2(0));
		exprRDiv = (Expression*)visit(ctx->exprLvl2(1));

		return (Expression*) new Division(exprGDiv, exprRDiv);
	}

      virtual antlrcpp::Any visitCasStandardLvl2(ifccParser::CasStandardLvl2Context *ctx) override {
            return (Expression*)visit(ctx->exprLvl2());
      }

      virtual antlrcpp::Any visitParenthese(ifccParser::ParentheseContext *ctx) override {
            return (Expression*)visit(ctx->expr());
      }
};