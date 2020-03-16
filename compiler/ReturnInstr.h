#pragma once

#include <string>

#include "Instruction.h"

class ReturnInstr : public Instruction {

public:
      //May change returnValue to Expression (variable, operation, etc...) 
      //when we will have to handle more complex behaviour
      ReturnInstr(int returnValue);
      ~ReturnInstr();

      std::string buildIR(CFG *cfg) override;

private:
      int returnValue;
};