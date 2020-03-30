//
//  Expression.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>
#include <iostream>

#include "Instruction.h"

/**
 * Subclass of the class Instruction which represents expression
 */
class Expression : public Instruction {

public:
      // Constructor
      Expression();
      // Destructor
      virtual ~Expression();

      /**
       * Abstract method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) = 0;
      // Abstract method that print the instruction
      void printInstruction(std::ostream &o) = 0;

      virtual void checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) = 0;

private:
      std::string returnType;
};