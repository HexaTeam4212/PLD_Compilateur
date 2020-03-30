//
//  ReturnInstr.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include <vector>
#include <string>

#include "ReturnInstr.h"
#include "CFG.h"

ReturnInstr::ReturnInstr(Expression* exprReturned)
: exprReturned(exprReturned)
{}

ReturnInstr::~ReturnInstr() {
      delete exprReturned;
}

std::string ReturnInstr::buildIR(CFG *cfg) {
      std::string retVarName = exprReturned->buildIR(cfg);
      IRVariable* retVar = cfg->getVariable(retVarName);

      std::vector<std::string> params;
      params.push_back(std::to_string(retVar->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::ret, params);
      return retVar->getName();
}

void ReturnInstr::checkVariableUsage(std::map<std::string, int>* mapVariableNames) {
      exprReturned->checkVariableUsage(mapVariableNames);
}

void ReturnInstr::printInstruction(std::ostream &o) {
      o << "\t\tReturn instruction" << std::endl << "\t\tValue returned : ";
      exprReturned->printInstruction(o);
}