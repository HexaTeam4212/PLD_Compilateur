//
//  ElseInstr.h
//  PLD-COMP
//
//  Created by H4212 on 01/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <vector> 

#include "Instruction.h"

/**
 * Subclass of the class Instruction which represents 'else'
 */
class ElseInstr : public Instruction {

public:
      // Constructor
      ElseInstr();
      // Destructor
      ~ElseInstr();

      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG *cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o, int shift) override;
      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;
      // Method that add a new instruction
      void addInstruction(Instruction* newInstruction);

private:
      std::vector<Instruction*> vectorInstruction;

};