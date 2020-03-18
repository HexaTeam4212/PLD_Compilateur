#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "CFG.h"

class Affectation : public Instruction {

public:
      Affectation(std::string varName, Expression* expr);
      ~Affectation();
      
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
      std::string varName;
      Expression* expr;
};