//
//  Declaration.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

//Interfaces used
#include <string>
#include <iostream>
#include <vector>

#include "Instruction.h"
#include "ExprVariable.h"

/**
 * Subclass of the class Instruction which represents declaration
 */
class DeclarationArg : public Instruction {

public:
      // Constructor
      DeclarationArg(std::vector<ExprVariable*> varsDeclared, std::vector<std::string > varsType);
      // Destructor
      ~DeclarationArg();

      // Getter of declarationArg type
	  std::vector<std::string >  getVarsType() { return varsType; };
      // Getter of argument declared variables
      std::vector<ExprVariable*> getVarsDeclared() { return varsDeclared; };
      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o, int shift) override;

      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;

private:
      std::vector<ExprVariable*> varsDeclared;
	std::vector<std::string >  varsType;
	static std::vector<std::string> registres;
};