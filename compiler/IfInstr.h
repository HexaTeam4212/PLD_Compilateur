//
//  IfInstr.h
//  PLD-COMP
//
//  Created by H4212 on 01/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

#include <vector>
#include <cstring>

#include "Instruction.h"
#include "Expression.h"
#include "ElseInstr.h"
#include "IRVariable.h"
#include "BasicBlock.h"

class IfInstr : public Instruction {

public:
      IfInstr();
      ~IfInstr();

      std::string buildIR(CFG *cfg) override;
      void printInstruction(std::ostream &o, int shift) override;
      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;

      void addInstructionIf(Instruction* newInstruction);

      void setCondition(Expression* c) { condition = c; };
      void setElseInstrution(ElseInstr* ei) { elseIntruction = ei; };


private:
      std::vector<Instruction*> vectorInstructionIf;
      ElseInstr* elseIntruction;
      Expression* condition;
};