#pragma once

#include <vector>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include "Program.h"
#include "Function.h"
#include "ReturnInstr.h"

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
            int returnValue = std::stoi(ctx->CONST()->getText());
            return (Instruction*) new ReturnInstr(returnValue);
      }

      virtual antlrcpp::Any visitInteger(ifccParser::IntegerContext *ctx) override {
            return (std::string) ctx->INTEGER()->getText();
      }

};