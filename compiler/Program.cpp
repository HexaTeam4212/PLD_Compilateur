//
//  Program.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Program.h"

Program::Program() 
{
      mapVariableNames = new std::map<std::string, int>();
}

Program::~Program() 
{}

void Program::checkFunctions() {
      for(Function* fPTR : functions) {
            fPTR->checkVariables(mapVariableNames);
      }

      std::map<std::string, int>::iterator it;
      for(it = mapVariableNames->begin(); it != mapVariableNames->end(); it++) {
            if(it->second == 0) {
                  std::string functionName = it->first.substr(0, it->first.find("!"));
                  std::string varName = it->first.substr(it->first.find("!")+1, it->first.size());

                  std::cerr << "Warning : variable \"" + varName + "\" is not used in function \"" + functionName + "\" !"  << std::endl;
            }
      }
}

void Program::addFunction(Function* functionToAdd) {
      functions.push_back(functionToAdd);
}

void Program::printProgram(std::ostream &o) {
      o << "#####################################" << std::endl;
      o << "Program" << std::endl << "Functions :" << std::endl;
      for(int i = 0; i < functions.size(); i++) {
            functions.at(i)->printFunction(o, 1);
      }
      o << "#####################################" << std::endl;
}