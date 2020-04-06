//
//  Instruction.h
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
#include <map>

class CFG;

/**
 * Abstract class that represent instruction inside a function 
 */
class Instruction {

public:
      // Constructor
      Instruction();
      // Destructor
      virtual ~Instruction();

      /**
       * Abstract method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      virtual std::string buildIR(CFG *cfg) = 0;
      // Abstract method that print the instruction
      virtual void printInstruction(std::ostream &o, int shift) = 0;

      virtual void checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) = 0;
};