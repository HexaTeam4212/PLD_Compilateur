#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "CFG.h"

class Soustraction : public Expression {

public:
	Soustraction(Expression* exprGDiff,Expression* exprRDiff);
      ~Soustraction();
      
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
	Expression* exprGDiff;
	Expression* exprRDiff;
};