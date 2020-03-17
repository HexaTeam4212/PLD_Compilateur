#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "Function.h"
#include "Declaration.h"

class Program {

public:
      Program();
      ~Program();

      void addFunction(Function* functionToAdd);
      std::vector<Function*> getAllFunctions() { return this->functions; };

      void printProgram(std::ostream &o);

private:
      std::vector<Function*> functions;
};