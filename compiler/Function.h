//
//  Function.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Instruction.h"
#include "ExprVariable.h"
#include "Declaration.h"

/**
 * Class that represents a function
 */
class Function {

public:
      // Constructor
      Function(std::string returnType, std::string name, Declaration* arguments);
      // Destructor
      ~Function();

      // Setters and getters
      void setName(std::string _name);
      std::string getName() { return this->name; };

      void setReturnType(std::string _returnType);
      std::string getReturnType() { return this->returnType; };

      void setInstructions(std::vector<Instruction*> _vectInstr);
      std::vector<Instruction*> getInstructions() { return this->instructions; };
	Declaration* getArguments() { return this->arguments; };

      // Print the function
      void printFunction(std::ostream &o, int shift);

      void checkVariables(std::map<std::string, int>* symbolTableNames);

	std::string buildIR(CFG *cfg);

	void printInstruction(std::ostream &o);

private:
      std::string name;
      std::string returnType;
      std::vector<Instruction*> instructions;
	Declaration* arguments;
};