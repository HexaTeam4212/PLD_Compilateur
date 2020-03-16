#include "BasicBlock.h"

BasicBlock::BasicBlock(CFG* cfg, std::string entry_label)
: cfg(cfg), label(entry_label)
{}

void BasicBlock::add_IRInstr(IRInstr::Operation op, std::vector<std::string> params) {
      IRInstr* newInstr = new IRInstr(this, op, params);
      instrs.push_back(newInstr);
}

void BasicBlock::gen_asm(std::ostream &o) {
      o << label + ":\n";
      for(IRInstr* instr : instrs) {
            instr->gen_asm(o);
      }
}