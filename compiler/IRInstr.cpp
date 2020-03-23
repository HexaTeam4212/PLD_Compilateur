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
          
   	case add :
            o << "\tmovq -" + params.at(0)+ "(%rbp), %rdx" << std::endl;
            o << "\tmovq -" + params.at(1)+ "(%rbp), %rax" << std::endl;
			o << "\taddq %rdx, %rax" << std::endl;
            o << "\tmovq  %rax, -" + params.at(2)+ "(%rbp)" << std::endl;
            break;
	case mult :
		o << "\tmovq -" + params.at(0) + "(%rbp), %rdx" << std::endl;
		o << "\tmovq -" + params.at(1) + "(%rbp), %rax" << std::endl;
		o << "\timul %rdx, %rax" << std::endl;
		o << "\tmovq  %rax, -" + params.at(2) + "(%rbp)" << std::endl;
		break;
	case diff:
		o << "\tmovq -" + params.at(0) + "(%rbp), %rdx" << std::endl;
		o << "\tmovq -" + params.at(1) + "(%rbp), %rax" << std::endl;
		o << "\tsubq %rdx, %rax" << std::endl;
		o << "\tmovq  %rax, -" + params.at(2) + "(%rbp)" << std::endl;
		break;
	case div:
		o << "\tmovq -" + params.at(0) + "(%rbp), %rax" << std::endl;
		//o << "\tmovq -" + params.at(1) + "(%rbp), %rax" << std::endl;
		o << "\tcqto" << std::endl;
		o << "\tidivq -" + params.at(1) + "(%rbp)" << std::endl;
		o << "\tmovq  %rax, -" + params.at(2) + "(%rbp)" << std::endl;
		break;
      default:
            break;
      }
}