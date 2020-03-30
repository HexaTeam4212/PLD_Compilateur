//
//  Addition.cpp
//  PLD-COMP
//
//  Created by H4212 on 22/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Addition.h"

Addition::Addition(Expression* exprGAdded, Expression* exprRAdded)
:exprGAdded(exprGAdded), exprRAdded(exprRAdded)
{}

Addition::~Addition() {
	delete exprGAdded;
	delete exprRAdded;
}

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

void Addition::checkVariableUsage(std::map<std::string, int>* mapVariableNames) {
	exprGAdded->checkVariableUsage(mapVariableNames);
	exprRAdded->checkVariableUsage(mapVariableNames);
}

void Addition::printInstruction(std::ostream &o) {
	o << "Addition of two expression" << std::endl;
	o << "\t\t\t\tExpr 1 : ";
	exprGAdded->printInstruction(o);
	o << "\t\t\t\tExpr 2 : ";
	exprRAdded->printInstruction(o);

}