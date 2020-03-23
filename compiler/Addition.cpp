#include "Addition.h"

Addition::Addition(Expression* exprGAdded, Expression* exprRAdded)
:exprGAdded(exprGAdded), exprRAdded(exprRAdded)
{}

Addition::~Addition()
{}

std::string Addition::buildIR(CFG* cfg) {
	std::string returnName = cfg->create_new_tempvar(Type::int64);
	IRVariable* varReturnName = cfg->getVariable(returnName);
	std::string exprG = exprGAdded->buildIR(cfg);
      IRVariable* varG = cfg->getVariable(exprG);
	std::string exprR = exprRAdded->buildIR(cfg);
      IRVariable* varR = cfg->getVariable(exprR);

      std::vector<std::string> params;
	params.push_back(std::to_string(varG->getOffset()));
      params.push_back(std::to_string(varR->getOffset()));
	params.push_back(std::to_string(varReturnName->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::add, params);
      
      return varReturnName->getName();
}

void Addition::printInstruction(std::ostream &o) {
      o << "\t\tAddition of origin into dest" << std::endl;
	  o << "\t\t\tOrigin Left & Right: ";
	  exprGAdded->printInstruction(o);
	  o << "&&&&&&&";
	  exprRAdded->printInstruction(o);
	  o << "\t\t\tDest : var temp " << std::endl;
}