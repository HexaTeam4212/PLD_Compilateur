#pragma once

#include <string>

#include "IRInstr.h"

class IRVariable {

public:
      IRVariable();
      ~IRVariable();

private:
      std::string name;
      Type varType;      
};