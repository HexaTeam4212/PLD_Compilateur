//
//  ExprVariable.h
//  PLD-COMP
//
//  Created by H4212 on 18/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <algorithm>

#include "Expression.h"

/**
 * Subclass of the class Expression which represents a variable
 */
class ExprVariable : public Expression {

public:
      // Constructor
      ExprVariable(std::string name);
      // Destructor
      ~ExprVariable();

      // Getter of the variable name
      std::string getName() { return name; };
      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o, int shift) override;

      virtual void checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) override;

private:
      std::string name;
};