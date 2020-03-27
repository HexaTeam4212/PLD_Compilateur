//
//  ExprConstante.h
//  PLD-COMP
//
//  Created by H4212 on 18/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>
#include <iostream>

#include "Expression.h"

/**
 * Subclass of the class Expression which represents a constant
 */
class ExprConstante : public Expression {

public:
      // Constructor
      ExprConstante(std::string value);
      // Destructor
      ~ExprConstante();

      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o) override;

private:
      std::string value;
};