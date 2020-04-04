#include "WhileInstr.h"

WhileInstr::WhileInstr()
{}

WhileInstr::~WhileInstr()
{}

std::string WhileInstr::buildIR(CFG *cfg) {
      // Create new block which will be used to jump to at the end of while loop
      std::string testBBName = cfg->new_BB_name();
      BasicBlock* testBB = new BasicBlock(cfg, testBBName);
      cfg->add_basicblock(testBB);

      testBB->exit_true = cfg->current_bb->exit_true;
      testBB->exit_false = cfg->current_bb->exit_false;
      cfg->current_bb->exit_true = testBB;
      cfg->current_bb->exit_false = nullptr;
      cfg->current_bb = testBB;

      std::string conditionVarName = condition->buildIR(cfg);

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
            if (strcmp(conditionVarName.c_str(), "jne") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JNE;
            }
            else if (strcmp(conditionVarName.c_str(), "jle") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JLE;
            }
            else if (strcmp(conditionVarName.c_str(), "jge") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JGE;
            }
            else if (strcmp(conditionVarName.c_str(), "jg") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JG;
            }
            else if (strcmp(conditionVarName.c_str(), "jl") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JL;
            }
            else if (strcmp(conditionVarName.c_str(), "je") == 0) {
                  cfg->current_bb->jumpType = BasicBlock::JumpType::JE;
            }
            // les autres comparaisons
      }

      std::string thenBBName = cfg->new_BB_name();
      BasicBlock* thenBB = new BasicBlock(cfg, thenBBName);
      cfg->add_basicblock(thenBB);

      std::string afterWhileBBName = cfg->new_BB_name();
      BasicBlock* afterWhileBB = new BasicBlock(cfg, afterWhileBBName);
      cfg->add_basicblock(afterWhileBB);
      
      afterWhileBB->exit_true = testBB->exit_true;
      afterWhileBB->exit_false = testBB->exit_false;

      testBB->exit_true = thenBB;
      testBB->exit_false = afterWhileBB;
      thenBB->exit_true = testBB;

      cfg->current_bb = thenBB;
      for(Instruction* instr : vectorInstruction) {
            instr->buildIR(cfg);
      }
      
      cfg->current_bb = afterWhileBB;

      return "";
}

void WhileInstr::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "While statement" << std::endl;
      o << std::string(shift, '\t') + "Condition : ";
      condition->printInstruction(o, shift+1);
      o << std::string(shift, '\t') + "Instructions : " << std::endl;
      for(Instruction* instr : vectorInstruction) {
            instr->printInstruction(o, shift+1);
      }
}

void WhileInstr::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
      for(Instruction* instrPTR : vectorInstruction) {
            instrPTR->checkVariableUsage(mapVariableNames, functionName);
      }
}

void WhileInstr::addInstruction(Instruction* newInstruction) {
      vectorInstruction.push_back(newInstruction);
}