#include "XorBit.h"

XorBit::XorBit(Expression* exprGXor, Expression* exprRXor)
: exprGXor(exprGXor), exprRXor(exprRXor)
{}

XorBit::~XorBit()
{}

std::string XorBit::buildIR(CFG* cfg) {
      std::string exprGName = exprGXor->buildIR(cfg);
      IRVariable* exprGVar = cfg->getVariable(exprGName);

      std::string exprRName = exprRXor->buildIR(cfg);
      IRVariable* exprRVar = cfg->getVariable(exprRName);

      std::string returnName = cfg->create_new_tempvar(Type::int64);
      IRVariable* returnVar = cfg->getVariable(returnName);

      std::vector<std::string> params;
	params.push_back(std::to_string(exprGVar->getOffset()));
	params.push_back(std::to_string(exprRVar->getOffset()));
      params.push_back(std::to_string(returnVar->getOffset()));
	cfg->current_bb->add_IRInstr(IRInstr::Operation::xorbit, params);

      return returnName;
}

void XorBit::printInstruction(std::ostream &o, int shift) {
      o << "Bitwise XOR operation between two expressions :" << std::endl;
      o << std::string(shift+1, '\t') + "Expr 1 : ";
	exprGXor->printInstruction(o, shift+1);
	o << std::string(shift+1, '\t') + "Expr 2 : ";
	exprRXor->printInstruction(o, shift+1);
}

void XorBit::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
      exprGXor->checkVariableUsage(mapVariableNames, functionName);
      exprRXor->checkVariableUsage(mapVariableNames, functionName);
}
