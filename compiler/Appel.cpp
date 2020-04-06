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

Appel::Appel(std::string nomFunction, std::string nomVar, std::vector<ExprVariable*> argumentsAppel) :
	nomFunction(nomFunction),nomVar(nomVar), argumentsAppel(argumentsAppel)
{}

Appel::~Appel() {
}

std::string Appel::buildIR(CFG* cfg) {
	IRVariable* laVar = cfg->getVariable(nomVar);

	// when there is function arguments
	//we move them into the corresponding register
	if (argumentsAppel.size()!=0) 
	{
		std::vector<std::string>::iterator it = registres.begin();

		for (ExprVariable* exprVar : argumentsAppel) {
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

	// c'est ici si on veut enlever le retour
	std::vector<std::string> params2;
	params2.push_back("%rax");
	params2.push_back("-" + std::to_string(laVar->getOffset()) + "(%rbp)");
	cfg->current_bb->add_IRInstr(IRInstr::Operation::movq, params2);

	return "";
}

void Appel::printInstruction(std::ostream &o) {
      o << "\t\tAppel of " << nomFunction <<"dans variable" << nomVar << std::endl;
    
}