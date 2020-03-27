//
//  Program.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "Function.h"
#include "Declaration.h"

/**
 * Class of a program
 */
class Program {

public:
      // Constructor
      Program();
      // Destructor
      ~Program();

      // Method to add a function for the program
      void addFunction(Function* functionToAdd);
      // Getter of the functions
      std::vector<Function*> getAllFunctions() { return this->functions; };

      // Method to print the program
      void printProgram(std::ostream &o);

private:
      std::vector<Function*> functions;
};