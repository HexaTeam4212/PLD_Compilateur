//
//  Declaration.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Appel.h"
#include "CFG.h"

std::vector<std::string> Appel::registres = { "%rdi","%rsi","%rdx","%rcx","%r8","%r9" };

Appel::Appel(std::string nomFunction, std::vector<Expression*> argumentsAppel) 
: nomFunction(nomFunction), argumentsAppel(argumentsAppel)
{}

Appel::~Appel() {
	for (Expression* argPTR : argumentsAppel) {
		delete argPTR;
	}
}

std::string Appel::buildIR(CFG* cfg) {

	// when there is function arguments
	//we move them into the corresponding register
	if (argumentsAppel.size()!=0) 
	{
		std::vector<std::string>::iterator it = registres.begin();

		for (Expression* exprVar : argumentsAppel) {
			std::string expr = exprVar->buildIR(cfg);
			IRVariable* var = cfg->getVariable(expr);
			std::vector<std::string> params;
			params.push_back("-"+std::to_string(var->getOffset())+"(%rbp)");
			params.push_back(*it);
			cfg->current_bb->add_IRInstr(IRInstr::Operation::movq, params);
			if (it != registres.end()){
				++it;
			}
		}

	}

	// function call
	std::vector<std::string> params1;
	params1.push_back("0");
	cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconstrax, params1);
	std::vector<std::string> params;
	params.push_back(nomFunction);
	cfg->current_bb->add_IRInstr(IRInstr::Operation::call, params);

	// put the return value in a temp var
	std::string tmpVarName = cfg->create_new_tempvar(Type::int64);
	IRVariable* tmpVar = cfg->getVariable(tmpVarName);
	std::vector<std::string> params2;
	params2.push_back("%rax");
	params2.push_back("-" + std::to_string(tmpVar->getOffset()) + "(%rbp)");
	cfg->current_bb->add_IRInstr(IRInstr::Operation::movq, params2);

	return tmpVarName;
}

void Appel::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "Call of " << nomFunction << std::endl;
    
}

void Appel::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
	for(Expression* varPTR : argumentsAppel) {
		varPTR->checkVariableUsage(symbolTableNames, functionName);
	}
}