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

void Declaration::checkVariableUsage(std::vector<std::string>* vectorVariableNames) {
      for(ExprVariable* varPTR : varsDeclared) {
            std::string currentVarName = varPTR->getName();
            std::vector<std::string>::iterator it = std::find(vectorVariableNames->begin(), vectorVariableNames->end(), currentVarName);
            
            if(it != vectorVariableNames->end()) {
                  //Error var declared twice
                  std::cerr << "Error : variable \"" + currentVarName +"\" is declared twice !" << std::endl;
                  exit(7); 
            }
            else {
                  vectorVariableNames->push_back(currentVarName);
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