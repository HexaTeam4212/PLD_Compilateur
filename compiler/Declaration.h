#pragma once

#include <string>

#include "Instruction.h"

class Declaration : public Instruction {

public:
      Declaration();
      ~Declaration();

      //getter setter

      std::string buildIR(CFG* cfg) override;

private:

      std::string type;
      std::string name;
};