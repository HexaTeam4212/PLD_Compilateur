#include "Egalite.h"

Egalite::Egalite(Expression* exprGMember, Expression* exprRMember)
:exprGMember(exprGMember), exprRMember(exprRMember)
{
    isBooleanExpr = true;
}

Egalite::~Egalite(){
    delete exprGMember;
    delete exprRMember;
}

std::string Egalite::buildIR(CFG* cfg) {
	std::string exprG = exprGMember->buildIR(cfg);
	IRVariable* varG = cfg->getVariable(exprG);
	std::string exprR = exprRMember->buildIR(cfg);
	IRVariable* varR = cfg->getVariable(exprR);

	std::vector<std::string> params;
	params.push_back(std::to_string(varG->getOffset()));
	params.push_back(std::to_string(varR->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::compare, params);

    const std::string jumpCmd = "?jne";

	return jumpCmd;
}

void Egalite::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
    exprRMember->checkVariableUsage(mapVariableNames, functionName);
    exprGMember->checkVariableUsage(mapVariableNames, functionName);
}

void Egalite::printInstruction(std::ostream &o) {
	o << "Equality of two expressions" << std::endl;
	o << "\t\t\t\tExpr 1 : ";
	exprGMember->printInstruction(o);
	o << "\t\t\t\tExpr 2 : ";
	exprRMember->printInstruction(o);
}