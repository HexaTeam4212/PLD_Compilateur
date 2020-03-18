#include <vector>
#include <string>

#include "ReturnInstr.h"
#include "CFG.h"

ReturnInstr::ReturnInstr(Expression* exprReturned)
: exprReturned(exprReturned)
{}

ReturnInstr::~ReturnInstr()
{}

std::string ReturnInstr::buildIR(CFG *cfg) {

      std::string retVarName = exprReturned->buildIR(cfg);
      IRVariable* retVar = cfg->getVariable(retVarName);

      std::vector<std::string> params;
      params.push_back(std::to_string(retVar->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::ret, params);
      return "";
}

void ReturnInstr::printInstruction(std::ostream &o) {
      o << "\t\tReturn instruction" << std::endl << "\t\tValue returned : ";
      exprReturned->printInstruction(o);
}