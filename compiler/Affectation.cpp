//
//  Affectation.cpp
//  PLD-COMP
//
//  Created by H4212 on 18/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Affectation.h"

Affectation::Affectation(std::string varName, Expression* expr) 
: varName(varName), expr(expr)
{}

Affectation::~Affectation() {
      delete expr;
}

std::string Affectation::buildIR(CFG* cfg) {
      IRVariable* varDest = cfg->getVariable(varName);
      std::string exprVarName = expr->buildIR(cfg);

      if(expr->getIsBooleanExpr()) {
            std::cerr << "Warning : affectation of boolean expression is not handled !" << std::endl;
            exit(-76);
      }

      IRVariable* varOrigin = cfg->getVariable(exprVarName);

      std::vector<std::string> params;
      params.push_back(std::to_string(varOrigin->getOffset()));
      params.push_back(std::to_string(varDest->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, params);

      return varDest->getName();
}

void Affectation::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      expr->checkVariableUsage(symbolTableNames, functionName);
}

void Affectation::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "Affectation of origin into dest" << std::endl;
      o << std::string(shift+1, '\t') + "Origin : ";
      expr->printInstruction(o, shift+2);
      o << std::string(shift+1, '\t') + "Dest : " << varName << std::endl;
}