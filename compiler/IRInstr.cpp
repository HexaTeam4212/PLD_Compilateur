#include "IRInstr.h"

IRInstr::IRInstr(BasicBlock* bb_, Operation op, std::vector<std::string> params)
: bb(bb_), op(op), params(params)
{}

void IRInstr::gen_asm(std::ostream &o) {
      switch (op)
      {
      case push:
            o << "\tpushq "+params.at(0)+"\n";
            break;
      
      case copy:
            o << "\tmovq "+params.at(0)+", "+params.at(1)+"\n";
            break;
      
      default:
            break;
      }
}