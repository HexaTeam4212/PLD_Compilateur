#pragma once

#include <string>
#include <vector>
#include <map>

#include "Function.h"
#include "BasicBlock.h"
#include "IRVariable.h"
#include "Declaration.h"

class CFG {

public:
      CFG(Function* ast);
      ~CFG();

      std::string new_BB_name();
      BasicBlock* gen_prologue(std::string functionName);
      BasicBlock* gen_epilogue(std::string functionName);
      BasicBlock* current_bb;
      
      int initTableVariable();
      std::string create_new_tempvar(Type type);

      IRVariable* getVariable(std::string nomVar);

      void gen_asm(std::ostream &o);

protected:

      std::map<std::string, IRVariable*> mapVariable;
      int nextFreeSymbolIndex;
      int nextBBnumber;
      int nextTempVarNumber;

private:
      int getOffsetBaseOnType(Type type);

      Function* ast;
      BasicBlock* CFGStart;
      int sizeAllocated;
};