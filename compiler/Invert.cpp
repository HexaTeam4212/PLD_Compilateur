#include "Invert.h"

Invert::Invert(Expression* exprMember)
: exprMember(exprMember)
{}

Invert::~Invert()
{}

std::string Invert::buildIR(CFG* cfg) {
      std::string returnName = cfg->create_new_tempvar(Type::int64);
      IRVariable* returnVar = cfg->getVariable(returnName);

      std::string exprName = exprMember->buildIR(cfg);
      IRVariable* exprVar = cfg->getVariable(exprName);

      std::vector<std::string> params;
      params.push_back(std::to_string(returnVar->getOffset()));
      params.push_back(std::to_string(exprVar->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::invert, params);

      return returnName;
}

void Invert::printInstruction(std::ostream &o, int shift) {
      o << "Invertion of an expression" << std::endl;
	o << std::string(shift+1, '\t') + "Expr : ";
	exprMember->printInstruction(o, shift+1);
}

void Invert::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
      exprMember->checkVariableUsage(mapVariableNames, functionName);
}