#pragma once

#include <vector>
#include <map>
#include <string>

#include "Function.h"
#include "Declaration.h"

class Program {

public:
      Program();
      ~Program();

      void addFunction(Function* functionToAdd);
      std::vector<Function*> getAllFunctions() { return this->functions; };

private:
      std::vector<Function*> functions;
};