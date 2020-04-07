//
//  IfInstr.h
//  PLD-COMP
//
//  Created by H4212 on 01/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <vector>
#include <cstring>

#include "Instruction.h"
#include "Expression.h"
#include "ElseInstr.h"
#include "IRVariable.h"
#include "BasicBlock.h"

/**
 * Subclass of the class Instruction which represents 'if'
 */
class IfInstr : public Instruction {

public:
      // Constructor
      IfInstr();
      // Destructor
      ~IfInstr();

      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG *cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o, int shift) override;
      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;
      // Method that add a new instruction
      void addInstructionIf(Instruction* newInstruction);
      // Method that set up the condition
      void setCondition(Expression* c) { condition = c; };
      // Method that set up an instruction 'else'
      void setElseInstrution(ElseInstr* ei) { elseIntruction = ei; };


private:
      std::vector<Instruction*> vectorInstructionIf;
      ElseInstr* elseIntruction;
      Expression* condition;
};