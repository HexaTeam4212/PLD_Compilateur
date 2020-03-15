#pragma once

#include <string>
#include <vector>

#include "Declaration.h"

class Function {

public:
      Function();
      ~Function();

      //getter setter here
      void setName(std::string _name);
      std::string getName() { return this->name; };

      void setReturnType(std::string _returnType);
      std::string getReturnType() { return this->returnType; };

      void setInstructions(std::vector<Instruction*> _vectInstr);
      std::vector<Instruction*> getInstructions() { return this->instructions; };

private:
      std::string name;
      std::string returnType;
      //std::vector<Declaration*> arguments;
      std::vector<Instruction*> instructions;
};