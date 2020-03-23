#include "Multiplication.h"

Multiplication::Multiplication(Expression* exprGMult, Expression* exprRMult)
:exprGMult(exprGMult), exprRMult(exprRMult)
{}

Multiplication::~Multiplication()
{}

std::string Multiplication::buildIR(CFG* cfg) {

	  std::string returnName = cfg->create_new_tempvar(Type::int64);
	  IRVariable* varReturnName = cfg->getVariable(returnName);
	  std::string exprG = exprGMult->buildIR(cfg);
      IRVariable* varG = cfg->getVariable(exprG);
	  std::string exprR = exprRMult->buildIR(cfg);
      IRVariable* varR = cfg->getVariable(exprR);

      std::vector<std::string> params;
	  params.push_back(std::to_string(varG->getOffset()));
      params.push_back(std::to_string(varR->getOffset()));
	  params.push_back(std::to_string(varReturnName->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::mult, params);
      
      return varReturnName->getName();
}

void Multiplication::printInstruction(std::ostream &o) {
      o << "\t\tMultplication of origin into dest" << std::endl;
      o << "\t\t\tOrigin : " << std::endl;
}