#include "SupOuEgalite.h"

SupOuEgalite::SupOuEgalite(Expression* exprGMember, Expression* exprRMember)
:exprGMember(exprGMember), exprRMember(exprRMember)
{
    isBooleanExpr = true;
}

SupOuEgalite::~SupOuEgalite(){
    delete exprGMember;
    delete exprRMember;
}

std::string SupOuEgalite::buildIR(CFG* cfg) {
	std::string exprG = exprGMember->buildIR(cfg);
	IRVariable* varG = cfg->getVariable(exprG);
	std::string exprR = exprRMember->buildIR(cfg);
	IRVariable* varR = cfg->getVariable(exprR);

	std::vector<std::string> params;
	params.push_back(std::to_string(varG->getOffset()));
	params.push_back(std::to_string(varR->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::compare, params);

    const std::string jumpCmd = "?jl";

	return jumpCmd;
}

void SupOuEgalite::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
    exprRMember->checkVariableUsage(mapVariableNames, functionName);
    exprGMember->checkVariableUsage(mapVariableNames, functionName);
}

void SupOuEgalite::printInstruction(std::ostream &o) {
	o << "Superiority or equality between two expressions" << std::endl;
	o << "\t\t\t\tExpr 1 : ";
	exprGMember->printInstruction(o);
	o << "\t\t\t\tExpr 2 : ";
	exprRMember->printInstruction(o);
}