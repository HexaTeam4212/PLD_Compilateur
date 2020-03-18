#include "Affectation.h"

Affectation::Affectation(std::string varName, Expression* expr) 
: varName(varName), expr(expr)
{}

Affectation::~Affectation()
{}

std::string Affectation::buildIR(CFG* cfg) {
      IRVariable* varDest = cfg->getVariable(varName);
      std::string exprVarName = expr->buildIR(cfg);
      IRVariable* varOrigin = cfg->getVariable(exprVarName);

      std::vector<std::string> params;
      params.push_back(std::to_string(varOrigin->getOffset()));
      params.push_back(std::to_string(varDest->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, params);

      return varDest->getName();
}

void Affectation::printInstruction(std::ostream &o) {
      o << "\t\tAffectation of origin into dest" << std::endl;
      o << "\t\t\tOrigin : ";
      expr->printInstruction(o);
      o << "\t\t\tDest : " << varName << std::endl;
}