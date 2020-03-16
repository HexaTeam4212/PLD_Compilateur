#include "CFG.h"

CFG::CFG(Function* ast)
{
      nextBBnumber = 0;
      BasicBlock* prologue = gen_prologue(ast->getName());
      BasicBlock* epilogue = gen_epilogue();
      BasicBlock* base = new BasicBlock(this, new_BB_name());
      prologue->exit_true = base;
      base->exit_true = epilogue;
      current_bb = base;
}

std::string CFG::new_BB_name() {
      std::string name("BB"+nextBBnumber);
      ++nextBBnumber;
      return name;
}

BasicBlock* CFG::gen_prologue(std::string functionName) {
      BasicBlock* prologue = new BasicBlock(this, functionName);
      
      std::vector<std::string> paramsPushRbp;
      paramsPushRbp.push_back("%rbp");
      IRInstr* pushRbp = new IRInstr(prologue, IRInstr::Operation::push, paramsPushRbp);

      std::vector<std::string> paramsMovRbpRsp;
      paramsMovRbpRsp.push_back("%rsp");
      paramsMovRbpRsp.push_back("%rbp");
      IRInstr* movRbpRsp = new IRInstr(prologue, IRInstr::Operation::copy, paramsMovRbpRsp);

      prologue->instrs.push_back(pushRbp);
      prologue->instrs.push_back(movRbpRsp);

      return prologue;
}