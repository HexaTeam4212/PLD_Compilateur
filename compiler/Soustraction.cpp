#include "Soustraction.h"

Soustraction::Soustraction(Expression* exprGDiff, Expression* exprRDiff)
:exprGDiff(exprGDiff), exprRDiff(exprRDiff)
{}

Soustraction::~Soustraction()
{}

std::string Soustraction::buildIR(CFG* cfg) {
	std::string returnName = cfg->create_new_tempvar(Type::int64);
	IRVariable* varReturnName = cfg->getVariable(returnName);
	std::string exprG = exprGDiff->buildIR(cfg);
      IRVariable* varG = cfg->getVariable(exprG);
	std::string exprR = exprRDiff->buildIR(cfg);
      IRVariable* varR = cfg->getVariable(exprR);

      std::vector<std::string> params;
	params.push_back(std::to_string(varG->getOffset()));
      params.push_back(std::to_string(varR->getOffset()));
	params.push_back(std::to_string(varReturnName->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::diff, params);
      
      return varReturnName->getName();
}

void Soustraction::printInstruction(std::ostream &o) {
      o << "\t\tSoustraction of origin into dest" << std::endl;
      o << "\t\t\tOrigin : " << std::endl;
}