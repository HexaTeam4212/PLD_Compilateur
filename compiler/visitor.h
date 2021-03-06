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
#include "IfInstr.h"
#include "Egalite.h"
#include "Superiorite.h"
#include "Inferiorite.h"
#include "SupOuEgalite.h"
#include "InfOuEgalite.h"
#include "Difference.h"
#include "Not.h"
#include "WhileInstr.h"
#include "Invert.h"
#include "EtBit.h"
#include "XorBit.h"
#include "OuBit.h"
#include "DeclareEtAffecte.h"

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
		Declaration* declationArgs = new Declaration(varArgument, "int");
		Function* function = new Function(returnType, functionName, declationArgs);
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
		std::string functionName = ctx->NAME()->getText();
		std::vector<Expression*> varArgumentAppel;
		if(ctx->expr().size() > 6 ) {
			std::cerr << "Error : function can have at most 6 parameters, sorry !" << std::endl;
			exit(-8);
		}

		for (int i = 0; i < ctx->expr().size(); i++) {
			Expression* newArgument = visit(ctx->expr().at(i));
			varArgumentAppel.push_back(newArgument);
		}
		return (Expression*) new Appel(functionName, varArgumentAppel);

	}

	virtual antlrcpp::Any visitCalling2(ifccParser::Calling2Context *ctx) override {
		std::string functionName = ctx->NAME()->getText();
		std::string varName;
		std::vector<Expression*> varArgumentAppel;
		if(ctx->expr().size() > 6 ) {
			std::cerr << "Error : function can have at most 6 parameters, sorry !" << std::endl;
			exit(-8);
		}

		for (int i = 0; i < ctx->expr().size(); i++) {
			Expression* newArgument = visit(ctx->expr().at(i));
			varArgumentAppel.push_back(newArgument);
		}
		return (Instruction*) new Appel(functionName, varArgumentAppel);

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
		  
		exprGAdded = (Expression*) visit(ctx->exprLvl0(0));
		exprRAdded = (Expression*) visit(ctx->exprLvl0(1));

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

      virtual antlrcpp::Any visitCasStandardLvl3(ifccParser::CasStandardLvl3Context *ctx) override {
            return (Expression*)visit(ctx->exprLvl3());
      }

      virtual antlrcpp::Any visitParenthese(ifccParser::ParentheseContext *ctx) override {
            return (Expression*)visit(ctx->expr());
      }

      virtual antlrcpp::Any visitIfstatement(ifccParser::IfstatementContext *ctx) override {
            IfInstr* ifInstruction = new IfInstr();

            ifInstruction->setCondition(visit(ctx->expr()));
            for(int i = 0; i < ctx->instr().size(); i++) {
                  Instruction* newInstr = visit(ctx->instr(i));
                  ifInstruction->addInstructionIf(newInstr);
            }

            if(ctx->elseStatement()) {
                  ElseInstr* elseInstruction = visit(ctx->elseStatement());
                  ifInstruction->setElseInstrution(elseInstruction);
            }

            return (Instruction*) ifInstruction;
      }

      virtual antlrcpp::Any visitElseStatement(ifccParser::ElseStatementContext *ctx) override {
            ElseInstr* elseInstruction = new ElseInstr();

            for(int i = 0; i < ctx->instr().size(); i++) {
                  Instruction* newInstr = visit(ctx->instr(i));
                  elseInstruction->addInstruction(newInstr);
            }

            return elseInstruction;
      }

      virtual antlrcpp::Any visitEgalite(ifccParser::EgaliteContext *ctx) override {
		Expression* exprGMember;
		Expression* exprRMember;
		  
		exprGMember = (Expression*) visit(ctx->exprLvl0(0));
		exprRMember = (Expression*) visit(ctx->exprLvl0(1));

		return (Expression*) new Egalite(exprGMember,exprRMember);
	}

      virtual antlrcpp::Any visitSuperiorite(ifccParser::SuperioriteContext *ctx) override {
		Expression* exprGMember;
		Expression* exprRMember;
		  
		exprGMember = (Expression*) visit(ctx->exprLvl0(0));
		exprRMember = (Expression*) visit(ctx->exprLvl0(1));

		return (Expression*) new Superiorite(exprGMember,exprRMember);
	}

      virtual antlrcpp::Any visitInferiorite(ifccParser::InferioriteContext *ctx) override {
	      Expression* exprGMember;
		Expression* exprRMember;
		  
		exprGMember = (Expression*) visit(ctx->exprLvl0(0));
		exprRMember = (Expression*) visit(ctx->exprLvl0(1));

		return (Expression*) new Inferiorite(exprGMember,exprRMember);
	}

      virtual antlrcpp::Any visitSupOuEgalite(ifccParser::SupOuEgaliteContext *ctx) override {
		Expression* exprGMember;
		Expression* exprRMember;
		  
		exprGMember = (Expression*) visit(ctx->exprLvl0(0));
		exprRMember = (Expression*) visit(ctx->exprLvl0(1));

		return (Expression*) new SupOuEgalite(exprGMember,exprRMember);
	}

      virtual antlrcpp::Any visitInfOuEgalite(ifccParser::InfOuEgaliteContext *ctx) override {
	      Expression* exprGMember;
		Expression* exprRMember;
		  
		exprGMember = (Expression*) visit(ctx->exprLvl0(0));
		exprRMember = (Expression*) visit(ctx->exprLvl0(1));

		return (Expression*) new InfOuEgalite(exprGMember,exprRMember);
	}

      virtual antlrcpp::Any visitDifference(ifccParser::DifferenceContext *ctx) override {
		Expression* exprGMember;
		Expression* exprRMember;
		  
		exprGMember = (Expression*) visit(ctx->exprLvl0(0));
		exprRMember = (Expression*) visit(ctx->exprLvl0(1));

		return (Expression*) new Difference(exprGMember,exprRMember);
	}


      virtual antlrcpp::Any visitNot(ifccParser::NotContext *ctx) override {
		Expression* exprMember;
		  
		exprMember = (Expression*) visit(ctx->exprLvl3());

		return (Expression*) new Not(exprMember);
	}

      virtual antlrcpp::Any visitWhilestatement(ifccParser::WhilestatementContext *ctx) override {
            WhileInstr* whileInstr = new WhileInstr();

            whileInstr->setCondition(visit(ctx->expr()));
            for(int i = 0; i < ctx->instr().size(); i++) {
                  Instruction* newInstr = visit(ctx->instr(i));
                  whileInstr->addInstruction(newInstr);
            }

            return (Instruction*) whileInstr;
      }

      virtual antlrcpp::Any visitInvert(ifccParser::InvertContext *ctx) override {
            Expression* exprMember;
		  
		exprMember = (Expression*) visit(ctx->exprLvl3());

		return (Expression*) new Invert(exprMember);
      }

      virtual antlrcpp::Any visitEtBit(ifccParser::EtBitContext *ctx) override {
            Expression* exprG = (Expression*) visit(ctx->expr(0));
            Expression* exprR = (Expression*) visit(ctx->expr(1));

            return (Expression*) new EtBit(exprG, exprR);
      }

      virtual antlrcpp::Any visitXorBit(ifccParser::XorBitContext *ctx) override {
            Expression* exprG = (Expression*) visit(ctx->expr(0));
            Expression* exprR = (Expression*) visit(ctx->expr(1));

            return (Expression*) new XorBit(exprG, exprR);
      }

      virtual antlrcpp::Any visitOuBit(ifccParser::OuBitContext *ctx) override {
            Expression* exprG = (Expression*) visit(ctx->expr(0));
            Expression* exprR = (Expression*) visit(ctx->expr(1));

            return (Expression*) new OuBit(exprG, exprR);
      }

      virtual antlrcpp::Any visitCasStandardLvl0(ifccParser::CasStandardLvl0Context *ctx) override {
            return (Expression*)visit(ctx->exprLvl0());
      }

	virtual antlrcpp::Any visitDeclareEtAffecte(ifccParser::DeclareEtAffecteContext *ctx) override {
		ExprVariable* var = new ExprVariable(ctx->NAME()->getText());
		std::vector<ExprVariable*> vars;
		vars.push_back(var);
		Declaration* dec = new Declaration(vars, visit(ctx->type()));
		Affectation* affec = new Affectation(ctx->NAME()->getText(), visit(ctx->expr()));

		return (Instruction*) new DeclareEtAffecte(dec, affec);
	}
};