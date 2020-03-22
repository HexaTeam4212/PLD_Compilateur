#pragma once

#include <string>
#include <iostream>

#include "Instruction.h"

class Expression : public Instruction {

public:
      Expression();
      ~Expression();

      std::string buildIR(CFG* cfg) = 0;
      void printInstruction(std::ostream &o) = 0;
	  //std::string getValue() = 0;

private:
      std::string returnType;
};