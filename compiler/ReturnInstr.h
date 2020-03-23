#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"

class ReturnInstr : public Instruction {

public:
      ReturnInstr(Expression* exprReturned);
      ~ReturnInstr();

      std::string buildIR(CFG *cfg) override;
      void printInstruction(std::ostream &o) override;
	  //std::string getValue() override = 0;

private:
      Expression* exprReturned;
};