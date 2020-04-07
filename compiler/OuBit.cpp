#include "OuBit.h"

OuBit::OuBit(Expression* exprGOu, Expression* exprROu)
: exprGOu(exprGOu), exprROu(exprROu)
{}

OuBit::~OuBit() {
      delete exprGOu;
      delete exprROu;
}

std::string OuBit::buildIR(CFG* cfg) {
      std::string exprGName = exprGOu->buildIR(cfg);
      IRVariable* exprGVar = cfg->getVariable(exprGName);

      std::string exprRName = exprROu->buildIR(cfg);
      IRVariable* exprRVar = cfg->getVariable(exprRName);

      std::string returnName = cfg->create_new_tempvar(Type::int64);
      IRVariable* returnVar = cfg->getVariable(returnName);

      std::vector<std::string> params;
	params.push_back(std::to_string(exprGVar->getOffset()));
	params.push_back(std::to_string(exprRVar->getOffset()));
      params.push_back(std::to_string(returnVar->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::orbit, params);

      return returnName;
}

void OuBit::printInstruction(std::ostream &o, int shift) {
      o << "Bitwise OR operation between two expressions :" << std::endl;
      o << std::string(shift+1, '\t') + "Expr 1 : ";
	exprGOu->printInstruction(o, shift+1);
	o << std::string(shift+1, '\t') + "Expr 2 : ";
	exprROu->printInstruction(o, shift+1);
}

void OuBit::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      exprGOu->checkVariableUsage(symbolTableNames, functionName);
      exprROu->checkVariableUsage(symbolTableNames, functionName);
}
