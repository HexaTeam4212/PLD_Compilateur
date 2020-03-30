//
//  Division.h
//  PLD-COMP
//
//  Created by H4212 on 23/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>

#include "Instruction.h"
#include "Expression.h"
#include "ExprConstante.h"
#include "CFG.h"

/**
 * Subclass of the class Expression which represents division
 */
class Division : public Expression {

public:
      // Constructor
	Division(Expression* exprGDiv,Expression* exprRDiv);
      // Destructor
      ~Division();
      
      /**
       * Method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Method that print the instruction
      void printInstruction(std::ostream &o) override;

      virtual void checkVariableUsage(std::map<std::string, int>* mapVariableNames) override;

private:
	Expression* exprGDiv;
	Expression* exprRDiv;
};