#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "CFG.h"

class Division : public Expression {

public:
	Division(Expression* exprGDiv,Expression* exprRDiv);
      ~Division();
      
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
	Expression* exprGDiv;
	Expression* exprRDiv;
};