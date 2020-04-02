//
//  CFG.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>
#include <vector>
#include <map>

#include "Function.h"
#include "BasicBlock.h"
#include "IRVariable.h"
#include "Declaration.h"
#include "Appel.h"

/**
 * Class that represent Control flow graph
 */
class CFG {

public:
      // Constructor
      CFG(Function* ast);
      // Destructor
      ~CFG();

      // Method to generate a new name for basic block
      static std::string new_BB_name();
      // Method to generate a prologue
      BasicBlock* gen_prologue(std::string functionName);
      // Method to generate an epilogue
      BasicBlock* gen_epilogue(std::string functionName);
      BasicBlock* current_bb;
      
      int initTableVariable();
      std::string create_new_tempvar(Type type);

      IRVariable* getVariable(std::string nomVar);

	  Function* getFunction(std::string nomFunction);
	  //std::string create_new_tempvar(Type type);

      void gen_asm(std::ostream &o);
	  std::string add_Function(Function* Function);

protected:
      std::map<std::string, IRVariable*> mapVariable;
      int nextFreeSymbolIndex; 
	  static std::map<std::string, Function*> mapFunction;
      static int nextBBnumber;
      int nextTempVarNumber;

private:
      int getOffsetBaseOnType(Type type);

      Function* ast;
      BasicBlock* CFGStart;
      int sizeAllocated;
};