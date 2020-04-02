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

Appel::Appel(std::string nomFunction, std::string nomVar) : 
	nomFunction(nomFunction),nomVar(nomVar)
{}

Appel::~Appel() {
}

std::string Appel::buildIR(CFG* cfg) {
	std::vector<std::string> params;
	params.push_back(nomFunction);
	cfg->current_bb->add_IRInstr(IRInstr::Operation::call, params);
	return "";
}

void Appel::printInstruction(std::ostream &o) {
      o << "\t\tAppel of " << nomFunction <<"dans variable" << nomVar << std::endl;
    
}