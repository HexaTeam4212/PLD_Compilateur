#pragma once

#include <string>
#include <vector>
#include <map>

#include "Function.h"
#include "BasicBlock.h"
#include "IRVariable.h"

class CFG {

public:
      CFG(Function* ast);
      ~CFG();

      std::string new_BB_name();
      BasicBlock* gen_prologue(std::string functionName);
      BasicBlock* gen_epilogue(std::string functionName);
      BasicBlock* current_bb;
      
      void gen_asm(std::ostream &o);

protected:

      std::map<std::string, IRVariable*> mapVariable;
      int nextFreeSymbolIndex;
      int nextBBnumber;

private:
      Function* ast;
      BasicBlock* CFGStart;
};