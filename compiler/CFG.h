#pragma once

#include <string>
#include <vector>
#include <map>

#include "Function.h"
#include "BasicBlock.h"
#include "IRVariable.h"

class CFG {

public:
      CFG();
      CFG(Function*);
      ~CFG();

      Function* ast;

      void add_bb(BasicBlock* bb);
      std::string new_BB_name();
      std::vector<BasicBlock> getAllBasicBlock();
      BasicBlock* gen_prologue(std::string functionName);
      BasicBlock* gen_epilogue();
      BasicBlock* current_bb;
      
      
      std::string gen_asm();
      std::string gen_asm_prologue();
      std::string gen_asm_epilogue();

protected:

      std::map<std::string, IRVariable*> mapVariable;
      int nextFreeSymbolIndex;
      int nextBBnumber;
private:

      std::vector<BasicBlock*> bbs;

};