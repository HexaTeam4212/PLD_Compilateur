#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "CFG.h"

class Multiplication : public Expression {

public:
      Multiplication(Expression* exprGmult,Expression* exprRMult);
      ~Multiplication();
      
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
	Expression* exprGMult;
	Expression* exprRMult;
};