#include "ExprConstante.h"
#include "CFG.h"

ExprConstante::ExprConstante(std::string value)
: value(value)
{}

ExprConstante::~ExprConstante()
{}

std::string ExprConstante::buildIR(CFG* cfg) {
      std::string varName = cfg->create_new_tempvar(Type::int64);
      IRVariable* var = cfg->getVariable(varName);

      //do a ldconst
      std::vector<std::string> params;
      params.push_back(value);
      params.push_back(std::to_string(var->getOffset()));
      cfg->current_bb->add_IRInstr(IRInstr::Operation::ldconst, params);

      return varName;
}

void ExprConstante::printInstruction(std::ostream &o) {
      o << "constant " << value << std::endl;
}