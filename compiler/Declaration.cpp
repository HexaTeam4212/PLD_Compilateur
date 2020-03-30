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

void Declaration::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
      for(ExprVariable* varPTR : varsDeclared) {
            std::string currentVarName = functionName + "!" + varPTR->getName();
            if(mapVariableNames->find(currentVarName) != mapVariableNames->end()) {
                  //Error var declared twice
                  std::cerr << "Error : variable \"" + varPTR->getName() +"\" is declared twice in "+ functionName +" !" << std::endl;
                  exit(7); 
            }
            else {
                  mapVariableNames->insert(std::make_pair(currentVarName, 0));
            }
      }
}

void Declaration::printInstruction(std::ostream &o) {
      o << "\t\tDeclaration of " << varsDeclared.size() << " variables" << std::endl;
      for(int i = 0; i < varsDeclared.size(); i++) {
            o << "\t\t\t";
            varsDeclared.at(i)->printInstruction(o);
      }
}