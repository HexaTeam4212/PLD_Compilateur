//
//  Declaration.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "DeclarationArg.h"
#include "CFG.h"

std::vector<std::string> DeclarationArg::registres = { "%rdi","%rsi","%rdx","%rcx","%r8","%r9" };

DeclarationArg::DeclarationArg(std::vector<ExprVariable*> varsDeclared, std::vector<std::string> varsType)
: varsDeclared(varsDeclared), varsType(varsType)
{}

DeclarationArg::~DeclarationArg() {
      for (ExprVariable* varPTR : varsDeclared) {
            delete varPTR;
      }
}

std::string DeclarationArg::buildIR(CFG* cfg) {


	std::vector<std::string>::iterator it = registres.begin();
	for (ExprVariable* exprVar : varsDeclared) {
		//if (dec->getType() == "int") { type = Type::int64; }
		std::string expr = exprVar->buildIR(cfg);
		IRVariable* var = cfg->getVariable(expr);
		std::vector<std::string> paramsArg;
		paramsArg.push_back(*it);
		paramsArg.push_back("-" + std::to_string(var->getOffset()) + "(%rbp)");
		
		++it;
		cfg->current_bb->add_IRInstr(IRInstr::Operation::movq, paramsArg);
	}

      return "";
}

void DeclarationArg::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "Declaration of Arguments " << varsDeclared.size() << " variables" << std::endl;
      for(int i = 0; i < varsDeclared.size(); i++) {
            o << std::string(shift+1, '\t');
            varsDeclared.at(i)->printInstruction(o, shift+1);
      }
}

void DeclarationArg::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {

}