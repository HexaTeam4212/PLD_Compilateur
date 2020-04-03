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
	std::cout << "appel" << std::endl;
	IRVariable* laVar = cfg->getVariable(nomVar);
	std::vector<std::string> params;
	params.push_back(nomFunction);
	params.push_back(std::to_string(laVar->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::call, params);
	std::cout << "fin appel" << std::endl;
	return "";
}

void Appel::printInstruction(std::ostream &o) {
      o << "\t\tAppel of " << nomFunction <<"dans variable" << nomVar << std::endl;
    
}