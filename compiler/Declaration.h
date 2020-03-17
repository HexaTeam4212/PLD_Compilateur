#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Instruction.h"
#include "ExprVariable.h"

class Declaration : public Instruction {

public:
      Declaration(std::vector<ExprVariable*> varsDeclared, std::string type);
      ~Declaration();

      std::string getType() { return type; };
      std::vector<ExprVariable*> getVarsDeclared() { return varsDeclared; };
      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
      std::vector<ExprVariable*> varsDeclared;
      std::string type;
};