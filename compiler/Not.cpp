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

	return varReturnName->getName();
}

void Not::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
    exprMember->checkVariableUsage(mapVariableNames, functionName);
}

void Not::printInstruction(std::ostream &o) {
	o << "Not of an expression" << std::endl;
	o << "\t\t\t\tExpr : ";
	exprMember->printInstruction(o);
}