#include "ExprVariable.h"
#include "CFG.h"

ExprVariable::ExprVariable(std::string name)
: name(name)
{}

ExprVariable::~ExprVariable()
{}

std::string ExprVariable::buildIR(CFG *cfg) {
      return cfg->getVariable(this->name)->getName();
}

void ExprVariable::printInstruction(std::ostream &o) {
      o << "variable " << this->name << std::endl;
}