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

void ExprVariable::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      auto it = symbolTableNames->find(functionName + "!" + this->name);
      if(it == symbolTableNames->end()) {
            //Error use of not declared variable
            std::cerr << "Error : variable \"" + this->name + "\" in the function " + functionName + " has not been declared !" << std::endl;
            exit(6);
      }
      else {
            it->second++;
      }

}

void ExprVariable::printInstruction(std::ostream &o, int shift) {
      o << "variable " << this->name << std::endl;
}