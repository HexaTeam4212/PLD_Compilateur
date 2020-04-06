//
//  Soustraction.cpp
//  PLD-COMP
//
//  Created by H4212 on 23/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Soustraction.h"

Soustraction::Soustraction(Expression* exprGDiff, Expression* exprRDiff)
:exprGDiff(exprGDiff), exprRDiff(exprRDiff)
{}

Soustraction::~Soustraction() {
	delete exprGDiff;
	delete exprRDiff;
}

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

void Soustraction::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
	exprGDiff->checkVariableUsage(symbolTableNames, functionName);
	exprRDiff->checkVariableUsage(symbolTableNames, functionName);
}

void Soustraction::printInstruction(std::ostream &o, int shift) {
	o << "Soustraction of two expression" << std::endl;
	o << std::string(shift+1, '\t') + "Expr 1 : ";
	exprGDiff->printInstruction(o, shift+1);
	o << std::string(shift+1, '\t') + "Expr 2 : ";
	exprRDiff->printInstruction(o, shift+1);
}