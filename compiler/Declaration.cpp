//
//  Declaration.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Declaration.h"
#include "CFG.h"

Declaration::Declaration(std::vector<ExprVariable*> varsDeclared, std::string type)
: varsDeclared(varsDeclared), type(type)
{}

Declaration::~Declaration() {
      for (ExprVariable* varPTR : varsDeclared) {
            delete varPTR;
      }
}

std::string Declaration::buildIR(CFG* cfg) {
      return "";
}

void Declaration::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      for(ExprVariable* varPTR : varsDeclared) {
            std::string currentVarName = functionName + "!" + varPTR->getName();
            if(symbolTableNames->find(currentVarName) != symbolTableNames->end()) {
                  //Error var declared twice
                  std::cerr << "Error : variable \"" + varPTR->getName() +"\" is declared twice in "+ functionName +" !" << std::endl;
                  exit(7); 
            }
            else {
                  symbolTableNames->insert(std::make_pair(currentVarName, 0));
            }
      }
}

void Declaration::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "Declaration of " << varsDeclared.size() << " variables" << std::endl;
      for(int i = 0; i < varsDeclared.size(); i++) {
            o << std::string(shift+1, '\t');
            varsDeclared.at(i)->printInstruction(o, shift+1);
      }
}