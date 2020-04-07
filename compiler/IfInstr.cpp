//
//  IfInstr.cpp
//  PLD-COMP
//
//  Created by H4212 on 01/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "IfInstr.h"

IfInstr::IfInstr()
: elseIntruction(nullptr)
{}

IfInstr::~IfInstr()
{}

std::string IfInstr::buildIR(CFG *cfg) {
      std::string conditionVarName = condition->buildIR(cfg);
      BasicBlock* testBB = cfg->current_bb;

      if (!condition->getIsBooleanExpr()){
            testBB->test_var_name = conditionVarName;
            IRVariable * var = cfg->getVariable(conditionVarName);

            std::string var_tmp_name = cfg->create_new_tempvar(Type::int64);
            IRVariable* var_tmp = cfg->getVariable(var_tmp_name);

            std::vector<std::string> params_tmp;
            params_tmp.push_back("0");
            params_tmp.push_back(std::to_string(var_tmp->getOffset()));
            cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, params_tmp);
            
            std::vector<std::string> params;
            params.push_back(std::to_string(var_tmp->getOffset()));
            params.push_back(std::to_string(var->getOffset()));
            cfg->current_bb->add_IRInstr(IRInstr::Operation::compare, params);
      }
      else {
            if (strcmp(conditionVarName.c_str(), "?jne") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JNE;
            }
            else if (strcmp(conditionVarName.c_str(), "?jle") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JLE;
            }
            else if (strcmp(conditionVarName.c_str(), "?jge") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JGE;
            }
            else if (strcmp(conditionVarName.c_str(), "?jg") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JG;
            }
            else if (strcmp(conditionVarName.c_str(), "?jl") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JL;
            }
            else if (strcmp(conditionVarName.c_str(), "?je") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JE;
            }
            // les autres comparaisons
      }

      std::string thenBBName = cfg->new_BB_name();
      BasicBlock* thenBB = new BasicBlock(cfg, thenBBName);
      cfg->add_basicblock(thenBB);

      std::string afterIfBBName = cfg->new_BB_name();
      BasicBlock* afterIfBB = new BasicBlock(cfg, afterIfBBName);
      cfg->add_basicblock(afterIfBB);
      
      afterIfBB->exit_true = testBB->exit_true;
      afterIfBB->exit_false = testBB->exit_false;

      // We assign pointers without considering existence of else
      testBB->exit_true = thenBB;
      testBB->exit_false = afterIfBB;
      thenBB->exit_true = afterIfBB;

      cfg->current_bb = thenBB;
      for(Instruction* instr : vectorInstructionIf) {
            instr->buildIR(cfg);
      }

      // If we have a else statement, we overwrite the exit false of testBB
      if(elseIntruction != nullptr) {
            std::string elseBBName = cfg->new_BB_name();
            BasicBlock* elseBB = new BasicBlock(cfg, elseBBName);
            cfg->add_basicblock(elseBB);

            testBB->exit_false = elseBB;
            elseBB->exit_true = afterIfBB;
            cfg->current_bb = elseBB;
            elseIntruction->buildIR(cfg);
      }
      
      cfg->current_bb = afterIfBB;

      return "";
}

void IfInstr::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "If statement" << std::endl;
      o << std::string(shift, '\t') + "Condition : ";
      condition->printInstruction(o, shift+1);
      o << std::string(shift, '\t') + "Instructions : " << std::endl;
      for(Instruction* instr : vectorInstructionIf) {
            instr->printInstruction(o, shift+1);
      }
      if(elseIntruction != nullptr) {
            elseIntruction->printInstruction(o, shift);
      }
}

void IfInstr::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      condition->checkVariableUsage(symbolTableNames, functionName);
      for(Instruction* instrPTR : vectorInstructionIf) {
            instrPTR->checkVariableUsage(symbolTableNames, functionName);
      }
}

void IfInstr::addInstructionIf(Instruction* newInstruction) {
      vectorInstructionIf.push_back(newInstruction);
}

