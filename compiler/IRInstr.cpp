#include "IRInstr.h"

IRInstr::IRInstr(BasicBlock* bb_, Operation op, std::vector<std::string> params)
: bb(bb_), op(op), params(params)
{}

void IRInstr::gen_asm(std::ostream &o) {
      switch (op)
      {
      case ldconst:
            o << "\tmovq $" + params.at(0) + ", -" + params.at(1) + "(%rbp)" << std::endl;
            break;
            
      case push:
            o << "\tpushq "+ params.at(0) << std::endl;
            break;

      case pop:
            o << "\tpopq "+ params.at(0) << std::endl;
            break;

      case ret:
            o << "\tmovq -"+ params.at(0) + "(%rbp), %rax" << std::endl;
            break;

      case exit:
            o << "\tret" << std::endl;
            break;
      
      case movq:
            o << "\tmovq " + params.at(0) + ", " + params.at(1) << std::endl;
            break;

      case copy:
            o << "\tmovq -" + params.at(0) + "(%rbp), %rax" << std::endl;
            o << "\tmovq %rax, -" + params.at(1) + "(%rbp)" << std::endl;
            break;

      default:
            break;
      }
}