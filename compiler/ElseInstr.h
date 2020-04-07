//
//  ElseInstr.h
//  PLD-COMP
//
//  Created by H4212 on 01/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//
#pragma once

#include <vector> 

#include "Instruction.h"

class ElseInstr : public Instruction {

public:
      ElseInstr();
      ~ElseInstr();

      std::string buildIR(CFG *cfg) override;
      void printInstruction(std::ostream &o, int shift) override;
      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;

      void addInstruction(Instruction* newInstruction);

private:
      std::vector<Instruction*> vectorInstruction;

};