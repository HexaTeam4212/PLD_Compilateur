#include "Declaration.h"
#include "CFG.h"

Declaration::Declaration(std::vector<ExprVariable*> varsDeclared, std::string type)
: varsDeclared(varsDeclared), type(type)
{}

Declaration::~Declaration()
{}

std::string Declaration::buildIR(CFG* cfg) {
      return "";
}

void Declaration::printInstruction(std::ostream &o) {
      o << "\t\tDeclaration of " << varsDeclared.size() << " variables" << std::endl;
      for(int i = 0; i < varsDeclared.size(); i++) {
            o << "\t\t\t";
            varsDeclared.at(i)->printInstruction(o);
      }
}