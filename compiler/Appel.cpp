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

Appel::Appel(std::string nomFunction, std::string nomVar, std::vector<ExprVariable*> argumentsAppel) :
	nomFunction(nomFunction),nomVar(nomVar), argumentsAppel(argumentsAppel)
{}

Appel::~Appel() {
}

std::string Appel::buildIR(CFG* cfg) {
	//différencier cas 0 arguments et cas avec arguments

	std::cout << "appel" << std::endl;
	IRVariable* laVar = cfg->getVariable(nomVar);
	

	//cas ou 0 arguments
	std::vector<std::string> params1;
	params1.push_back("0");
	cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconstrax, params1);
	std::vector<std::string> params;
	params.push_back(nomFunction);
	cfg->current_bb->add_IRInstr(IRInstr::Operation::call, params);
	std::vector<std::string> params2;
	params2.push_back("%rax");
	params2.push_back(std::to_string(laVar->getOffset()) + "(%rbp)");
	cfg->current_bb->add_IRInstr(IRInstr::Operation::movq, params2);
	std::cout << "fin appel" << std::endl;
	return "";
}

void Appel::printInstruction(std::ostream &o) {
      o << "\t\tAppel of " << nomFunction <<"dans variable" << nomVar << std::endl;
    
}