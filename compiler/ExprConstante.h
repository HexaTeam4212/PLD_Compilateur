#pragma once

#include <string>
#include <iostream>

#include "Expression.h"

class ExprConstante : public Expression {

public:
      ExprConstante(std::string value);
      ~ExprConstante();

      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
      std::string value;
};