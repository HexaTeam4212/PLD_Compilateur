//
//  Multiplication.cpp
//  PLD-COMP
//
//  Created by H4212 on 23/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Multiplication.h"

Multiplication::Multiplication(Expression* exprGMult, Expression* exprRMult)
:exprGMult(exprGMult), exprRMult(exprRMult)
{}

Multiplication::~Multiplication() {
	delete exprGMult;
	delete exprRMult;
}

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

void Multiplication::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
	exprGMult->checkVariableUsage(mapVariableNames, functionName);
	exprRMult->checkVariableUsage(mapVariableNames, functionName);
}

void Multiplication::printInstruction(std::ostream &o, int shift) {
	o << "Multiplication of two expression" << std::endl;
	o << std::string(shift+1, '\t') + "Expr 1 : ";
	exprGMult->printInstruction(o, shift+1);
	o << std::string(shift+1, '\t') + "Expr 2 : ";
	exprRMult->printInstruction(o, shift+1);
}