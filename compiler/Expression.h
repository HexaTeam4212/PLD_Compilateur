#pragma once

#include "Instruction.h"

class Expression : public Instruction {

public:
      Expression();
      ~Expression();

private:
      std::string returnType;
};