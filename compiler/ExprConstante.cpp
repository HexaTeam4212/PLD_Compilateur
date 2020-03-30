//
//  ExprConstante.cpp
//  PLD-COMP
//
//  Created by H4212 on 18/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "ExprConstante.h"
#include "CFG.h"

ExprConstante::ExprConstante(std::string value)
: value(value)
{}

ExprConstante::~ExprConstante()
{}

std::string ExprConstante::buildIR(CFG* cfg) {
      std::string varName = cfg->create_new_tempvar(Type::int64);
      IRVariable* var = cfg->getVariable(varName);

      //do a ldconst
      std::vector<std::string> params;
      params.push_back(value);
      params.push_back(std::to_string(var->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, params);

      return varName;
}

void ExprConstante::checkVariableUsage(std::vector<std::string>* vectorVariableNames) {}

void ExprConstante::printInstruction(std::ostream &o) {
      o << "constant " << value << std::endl;
}