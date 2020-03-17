#pragma once

#include <string>
#include <iostream>

#include "Instruction.h"

class Declaration : public Instruction {

public:
      Declaration();
      ~Declaration();

      //getter setter

      std::string buildIR(CFG* cfg) override;
      void printInstruction(std::ostream &o) override;

private:

      std::string type;
      std::string name;
};