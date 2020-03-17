#pragma once

#include <string>
#include <iostream>

#include "Instruction.h"

class Expression : public Instruction {

public:
      Expression();
      ~Expression();

      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:
      std::string returnType;
};