//
//  SupOuEgalite.cpp
//  PLD-COMP
//
//  Created by H4212 on 02/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "SupOuEgalite.h"

SupOuEgalite::SupOuEgalite(Expression* exprGMember, Expression* exprRMember)
:exprGMember(exprGMember), exprRMember(exprRMember)
{
    isBooleanExpr = true;
}

SupOuEgalite::~SupOuEgalite(){
    delete exprGMember;
    delete exprRMember;
}

std::string SupOuEgalite::buildIR(CFG* cfg) {
	std::string exprG = exprGMember->buildIR(cfg);
	IRVariable* varG = cfg->getVariable(exprG);
	std::string exprR = exprRMember->buildIR(cfg);
	IRVariable* varR = cfg->getVariable(exprR);

	std::vector<std::string> params;
	params.push_back(std::to_string(varG->getOffset()));
	params.push_back(std::to_string(varR->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::compare, params);

    const std::string jumpCmd = "?jl";

	return jumpCmd;
}

void SupOuEgalite::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
    exprRMember->checkVariableUsage(symbolTableNames, functionName);
    exprGMember->checkVariableUsage(symbolTableNames, functionName);
}

void SupOuEgalite::printInstruction(std::ostream &o, int shift) {
	o << "Superiority or equality between two expressions" << std::endl;
	o << std::string(shift+1, '\t') + "Expr 1 : ";
	exprGMember->printInstruction(o, shift+1);
	o << std::string(shift+1, '\t') + "Expr 2 : ";
	exprRMember->printInstruction(o, shift+1);
}