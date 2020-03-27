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
{}

Program::~Program() 
{}

void Program::addFunction(Function* functionToAdd) {
      functions.push_back(functionToAdd);
}

void Program::printProgram(std::ostream &o) {
      o << "#####################################" << std::endl;
      o << "Program" << std::endl << "Functions :" << std::endl;
      for(int i = 0; i < functions.size(); i++) {
            functions.at(i)->printFunction(o);
      }
      o << "#####################################" << std::endl;
}