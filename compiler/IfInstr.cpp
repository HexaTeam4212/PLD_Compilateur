#include "IfInstr.h"

IfInstr::IfInstr()
: elseIntruction(nullptr)
{}

IfInstr::~IfInstr()
{}

std::string IfInstr::buildIR(CFG *cfg) {
      std::string conditionVarName = condition->buildIR(cfg);
      BasicBlock* testBB = cfg->current_bb;
      testBB->test_var_name = conditionVarName;
      std::string thenBBName = cfg->new_BB_name();
      BasicBlock* thenBB = new BasicBlock(cfg, thenBBName);
      std::string afterIfBBName = cfg->new_BB_name();
      BasicBlock* afterIfBB = new BasicBlock(cfg, afterIfBBName);
      
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
            testBB->exit_false = elseBB;
            elseBB->exit_true = afterIfBB;
            cfg->current_bb = elseBB;
            elseIntruction->buildIR(cfg);
      }
      
      cfg->current_bb = afterIfBB;

      return "";
}

void IfInstr::printInstruction(std::ostream &o) {}

void IfInstr::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {}

void IfInstr::addInstructionIf(Instruction* newInstruction) {
      vectorInstructionIf.push_back(newInstruction);
}
