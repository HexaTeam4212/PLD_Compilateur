//
//  ExprVariable.cpp
//  PLD-COMP
//
//  Created by H4212 on 18/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "ExprVariable.h"
#include "CFG.h"

ExprVariable::ExprVariable(std::string name)
: name(name)
{}

ExprVariable::~ExprVariable()
{}

std::string ExprVariable::buildIR(CFG *cfg) {
      return cfg->getVariable(this->name)->getName();
}

void ExprVariable::checkVariableUsage(std::vector<std::string>* vectorVariableNames) {
      std::vector<std::string>::iterator it = std::find(vectorVariableNames->begin(), vectorVariableNames->end(), this->name);
      if(it == vectorVariableNames->end()) {
            //Error use of not declared variable
            std::cerr << "Error : variable \"" + this->name + "\" has not been declared !" << std::endl;
            exit(6);
      }
}

void ExprVariable::printInstruction(std::ostream &o) {
      o << "variable " << this->name << std::endl;
}