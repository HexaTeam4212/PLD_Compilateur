#pragma once

#include "Expression.h"

class ExprVariable : public Expression {

public:
      ExprVariable(std::string name);
      ~ExprVariable();

      std::string getName() { return name; };
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;
	  //std::string getValue() override;

private:
      std::string name;
};