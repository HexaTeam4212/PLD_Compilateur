#pragma once

#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "CFG.h"

class Addition : public Instruction {

public:
      Addition(std::string varName, std::vector<Expression*> exprAdded);
      ~Addition();
      
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
      std::string varName;
	  std::vector<Expression*> exprAdded;
};