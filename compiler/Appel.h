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
class Appel : public Instruction {

public:
      // Constructor
      Appel(std::string nomFunction, std::string nomVar, std::vector<ExprVariable*> argumentsAppel);
      // Destructor
      ~Appel();

      // Getter of declaration type
      //std::string getType() { return type; };
      // Getter of declared variables
      //std::vector<ExprVariable*> getVarsDeclared() { return varsDeclared; };
      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o) override;

private:
	std::string nomFunction;
	std::string nomVar;
	std::vector<ExprVariable*> argumentsAppel;
	static std::vector<std::string> registres;
};