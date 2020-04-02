//
//  InfOuEgalite.h
//  PLD-COMP
//
//  Created by H4212 on 02/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>

#include "Expression.h"
#include "CFG.h"
#include "Instruction.h"

/**
 * Subclass of the class Expression which represents inferiority or equality test
 */
class InfOuEgalite : public Expression {

public:
    // Constructor
    InfOuEgalite(Expression* exprGMember, Expression* exprRMember);
    // Destructor
    ~InfOuEgalite();
      
    /**
    * Method that build an IR (Intermediate Representation)
    * for a CFG (Control Flow Graph)
    */
    std::string buildIR(CFG* cfg) override;
    // Method that print the instruction
    void printInstruction(std::ostream &o) override;

    void checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) override;

private:
	Expression* exprGMember;
	Expression* exprRMember;

};