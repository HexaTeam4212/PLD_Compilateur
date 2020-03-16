#include "Program.h"

Program::Program() 
{}

Program::~Program() 
{}

void Program::addFunction(Function* functionToAdd) {
      functions.push_back(functionToAdd);
}