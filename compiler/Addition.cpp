#include "Addition.h"

Addition::Addition(std::string varName, std::vector<Expression*> exprAdded)
: varName(varName), exprAdded(exprAdded)
{}

Addition::~Addition()
{}

std::string Addition::buildIR(CFG* cfg) {
		
	  std::string unRes = "7";
	  ExprConstante* exprRes = new ExprConstante(unRes);

	  for (auto it = std::begin(exprAdded); it != std::end(exprAdded); ++it) {
		  //(*it)->getValue();

	  }

      IRVariable* varDest = cfg->getVariable(varName);
	  std::string exprVarName = exprRes->buildIR(cfg);
      IRVariable* varOrigin = cfg->getVariable(exprVarName);
      std::vector<std::string> params;
      params.push_back(std::to_string(varOrigin->getOffset()));
      params.push_back(std::to_string(varDest->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, params);
      return varDest->getName();

}

void Addition::printInstruction(std::ostream &o) {
      o << "\t\tAddition of origin into dest" << std::endl;
      o << "\t\t\tOrigin : " << std::endl;
	  /*
	  for (auto it = std::begin(exprAdded); it != std::end(exprAdded); ++it) {
		  o << it->printInstruction(o) << std::endl;
	  }*/
      o << "\t\t\tDest : " << varName << std::endl;
}