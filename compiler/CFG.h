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
#include "Affectation.h"

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
      std::string new_BB_name();
      // Method to generate a prologue
      BasicBlock* gen_prologue(std::string functionName);
      // Method to generate an epilogue
      BasicBlock* gen_epilogue(std::string functionName);
      void add_basicblock(BasicBlock* newBB);
      BasicBlock* current_bb;
      
      int initSymbolTable();
      std::string create_new_tempvar(Type type);
      IRVariable* getVariable(std::string nomVar);

      void gen_asm(std::ostream &o);

protected:
      std::map<std::string, IRVariable*> symbolTable;
      int nextFreeSymbolIndex;
      int nextBBnumber;
      int nextTempVarNumber;

private:
      int getOffsetBaseOnType(Type type);

      Function* ast;
      BasicBlock* CFGStart;
      int sizeAllocated;
      std::vector<BasicBlock*> allBBs;
};