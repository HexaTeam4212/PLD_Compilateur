//
//  OuBit.h
//  PLD-COMP
//
//  Created by H4212 on 06/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

#include "Expression.h"
#include "CFG.h"

class OuBit : public Expression {

public:
      // Constructor
      OuBit(Expression* exprGOu, Expression* exprROu);
      // Destructor
      virtual ~OuBit();

      /**
       * Abstract method that build an IR (Intermediate Representation)
       * for a CFG (Control Flow Graph)
       */
      std::string buildIR(CFG* cfg) override;
      // Abstract method that print the instruction
      void printInstruction(std::ostream &o, int shift) override;

      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;

private:
      Expression* exprGOu;
      Expression* exprROu;
};