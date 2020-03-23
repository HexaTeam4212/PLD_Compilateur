#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "CFG.h"

class Addition : public Expression {

public:
      Addition(Expression* exprGAdded,Expression* exprRAdded);
      ~Addition();
      
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
	  Expression* exprGAdded;
	  Expression* exprRAdded;
};