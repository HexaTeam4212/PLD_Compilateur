#pragma once

#include <string>

#include "IRInstr.h"

class IRVariable {

public:
      IRVariable(std::string name, Type type, int offset);
      ~IRVariable();

      std::string getName() { return name; };
      Type getVarType() { return varType; };
      int getOffset() { return offset; };

private:
      std::string name;
      Type varType;
      int offset;
};