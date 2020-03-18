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