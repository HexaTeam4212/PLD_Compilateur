#include <vector>
#include <string>

#include "ReturnInstr.h"
#include "CFG.h"

ReturnInstr::ReturnInstr(int returnValue)
: returnValue(returnValue)
{}

ReturnInstr::~ReturnInstr()
{}

std::string ReturnInstr::buildIR(CFG *cfg)
{
      std::vector<std::string> params;
      params.push_back("$"+std::to_string(returnValue));
      params.push_back("%rax");
      cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, params);
      return "";
}