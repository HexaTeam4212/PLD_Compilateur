#include "CFG.h"

#include <iostream>
#include <fstream>

CFG::CFG(Function* ast)
{
      nextBBnumber = 0;
      BasicBlock* prologue = gen_prologue(ast->getName());
      BasicBlock* base = new BasicBlock(this, new_BB_name());
      BasicBlock* epilogue = gen_epilogue(ast->getName());
      prologue->exit_true = base;
      base->exit_true = epilogue;
      current_bb = base;
      CFGStart = prologue;

      for(auto instr : ast->getInstructions()) {
            instr->buildIR(this);
      }
}

std::string CFG::new_BB_name() {
      std::string name("BB"+ std::to_string(nextBBnumber));
      ++nextBBnumber;
      return name;
}

BasicBlock* CFG::gen_prologue(std::string functionName) {
      BasicBlock* prologue = new BasicBlock(this, functionName);
      
      std::vector<std::string> paramsPushRbp;
      paramsPushRbp.push_back("%rbp");
      prologue->add_IRInstr(IRInstr::Operation::push, paramsPushRbp);

      std::vector<std::string> paramsMovRbpRsp;
      paramsMovRbpRsp.push_back("%rsp");
      paramsMovRbpRsp.push_back("%rbp");
      prologue->add_IRInstr(IRInstr::Operation::copy, paramsMovRbpRsp);

      return prologue;
}

BasicBlock* CFG::gen_epilogue(std::string functionName) {
      BasicBlock* epilogue = new BasicBlock(this, "end"+functionName);

      std::vector<std::string> paramsPopRbp;
      paramsPopRbp.push_back("%rbp");
      epilogue->add_IRInstr(IRInstr::Operation::pop, paramsPopRbp);

      std::vector<std::string> paramsRet;
      epilogue->add_IRInstr(IRInstr::Operation::ret, paramsRet);

      return epilogue;
}

void CFG::gen_asm(std::ostream &o) {

      current_bb = CFGStart;

      o << ".text\n";
      o << ".global main\n";

      while(current_bb != nullptr) {
            current_bb->gen_asm(o);

            if(current_bb->exit_true != nullptr && current_bb->exit_false != nullptr) {
                  //conditionnal jump
                  std::cout << "Conditional jump not handle" << std::endl;
                  current_bb = nullptr;
            }
            else {
                  current_bb = current_bb->exit_true;
            }
      }
}