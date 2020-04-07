//
//  Not.cpp
//  PLD-COMP
//
//  Created by H4212 on 05/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Not.h"

Not::Not(Expression* exprMember)
:exprMember(exprMember)
{
    isBooleanExpr = false;
}

Not::~Not(){
    delete exprMember;
}

std::string Not::buildIR(CFG* cfg) {

    std::string returnName = cfg->create_new_tempvar(Type::int64);
    IRVariable* varReturnName = cfg->getVariable(returnName);

    std::string expr = exprMember->buildIR(cfg);

    if(expr[0] != '?') {
        IRVariable* var = cfg->getVariable(expr);

        // Creer constante 0
        std::string var_tmp_name = cfg->create_new_tempvar(Type::int64);
        IRVariable* var_tmp = cfg->getVariable(var_tmp_name);

        std::vector<std::string> params_tmp;
        params_tmp.push_back("0");
        params_tmp.push_back(std::to_string(var_tmp->getOffset()));
        cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, params_tmp);
        
        //Comparer 0 a l'expression apres le !
        std::vector<std::string> params;
        params.push_back(std::to_string(var_tmp->getOffset()));
        params.push_back(std::to_string(var->getOffset()));
        cfg->current_bb->add_IRInstr(IRInstr::Operation::compare, params);

        //Stocker la valeur du !expr dans varReturnName
        std::vector<std::string> params_var;
        params_var.push_back(std::to_string(varReturnName->getOffset()));
        cfg->current_bb->add_IRInstr(IRInstr::Operation::non, params_var);
    } else {
        if (strcmp(expr.c_str(), "?jne") == 0) {
            returnName = "?je";
        }
        else if (strcmp(expr.c_str(), "?jle") == 0) {
            returnName = "?jg";
        }
        else if (strcmp(expr.c_str(), "?jge") == 0) {
            returnName = "?jl";
        }
        else if (strcmp(expr.c_str(), "?jg") == 0) {
            returnName = "?jle";
        }
        else if (strcmp(expr.c_str(), "?jl") == 0) {
            returnName = "?jge";
        }
        else if (strcmp(expr.c_str(), "?je") == 0) {
            returnName = "?jne";
        }
        isBooleanExpr = true;
    }

	return returnName;
}

void Not::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
    exprMember->checkVariableUsage(symbolTableNames, functionName);
}

void Not::printInstruction(std::ostream &o, int shift) {
	o << "Not of an expression" << std::endl;
	o << std::string(shift+1, '\t') + "Expr : ";
	exprMember->printInstruction(o, shift+1);
}