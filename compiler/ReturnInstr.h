//
//  ReturnInstr.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>

#include "Instruction.h"
#include "Expression.h"

/**
 * Subclass of the class Instruction which represents a return expression
 */
class ReturnInstr : public Instruction {

public:
      // Constructor
      ReturnInstr(Expression* exprReturned);
      // Destructor
      ~ReturnInstr();

      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o, int shift) override;

      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;

private:
      Expression* exprReturned;
};