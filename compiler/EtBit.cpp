#include "EtBit.h"

EtBit::EtBit(Expression* exprGEt, Expression* exprREt)
: exprGEt(exprGEt), exprREt(exprREt)
{}

EtBit::~EtBit() {
      delete exprGEt;
      delete exprREt;
}

std::string EtBit::buildIR(CFG* cfg) {
      std::string exprGName = exprGEt->buildIR(cfg);
      IRVariable* exprGVar = cfg->getVariable(exprGName);

      std::string exprRName = exprREt->buildIR(cfg);
      IRVariable* exprRVar = cfg->getVariable(exprRName);

      std::string returnName = cfg->create_new_tempvar(Type::int64);
      IRVariable* returnVar = cfg->getVariable(returnName);

      std::vector<std::string> params;
	params.push_back(std::to_string(exprGVar->getOffset()));
	params.push_back(std::to_string(exprRVar->getOffset()));
      params.push_back(std::to_string(returnVar->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::andbit, params);

      return returnName;
}

void EtBit::printInstruction(std::ostream &o, int shift) {
      o << "Bitwise AND operation between two expressions :" << std::endl;
      o << std::string(shift+1, '\t') + "Expr 1 : ";
	exprGEt->printInstruction(o, shift+1);
	o << std::string(shift+1, '\t') + "Expr 2 : ";
	exprREt->printInstruction(o, shift+1);
}

void EtBit::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      exprGEt->checkVariableUsage(symbolTableNames, functionName);
      exprREt->checkVariableUsage(symbolTableNames, functionName);
}
