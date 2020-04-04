//
//  WhileInstr.h
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
#include "IRVariable.h"
#include "BasicBlock.h"

class WhileInstr : public Instruction {

public:
      WhileInstr();
      ~WhileInstr();

      std::string buildIR(CFG *cfg) override;
      void printInstruction(std::ostream &o) override;
      virtual void checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) override;

      void addInstruction(Instruction* newInstruction);

      void setCondition(Expression* c) { condition = c; };

private:
      std::vector<Instruction*> vectorInstruction;
      Expression* condition;
};