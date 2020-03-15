#include "Function.h"

Function::Function()
{}

Function::~Function()
{}

void Function::setName(std::string _name)
{
      this->name = _name;
}

void Function::setReturnType(std::string _returnType)
{
      this->returnType = _returnType;
}

void Function::setInstructions(std::vector<Instruction*> _vectInstr)
{
      this->instructions = _vectInstr;
}