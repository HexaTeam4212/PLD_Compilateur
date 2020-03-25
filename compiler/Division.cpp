#include "Division.h"

Division::Division(Expression* exprGDiv, Expression* exprRDiv)
:exprGDiv(exprGDiv), exprRDiv(exprRDiv)
{}

Division::~Division()
{}

std::string Division::buildIR(CFG* cfg) {
	std::string returnName = cfg->create_new_tempvar(Type::int64);
	IRVariable* varReturnName = cfg->getVariable(returnName);
	std::string exprG = exprGDiv->buildIR(cfg);
      IRVariable* varG = cfg->getVariable(exprG);
	std::string exprR = exprRDiv->buildIR(cfg);
      IRVariable* varR = cfg->getVariable(exprR);

      std::vector<std::string> params;
	params.push_back(std::to_string(varG->getOffset()));
      params.push_back(std::to_string(varR->getOffset()));
	params.push_back(std::to_string(varReturnName->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::div, params);
      
      return varReturnName->getName();
}

void Division::printInstruction(std::ostream &o) {
      o << "Division of two expression" << std::endl;
	o << "\t\t\t\tExpr 1 : ";
	exprGDiv->printInstruction(o);
	o << "\t\t\t\tExpr 2 : ";
	exprRDiv->printInstruction(o);
}