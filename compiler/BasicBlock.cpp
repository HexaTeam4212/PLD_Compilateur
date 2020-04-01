//
//  BasicBlock.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "BasicBlock.h"

BasicBlock::BasicBlock(CFG* cfg, std::string entry_label)
: cfg(cfg), label(entry_label), exit_true(nullptr), exit_false(nullptr)
{}

BasicBlock::~BasicBlock() {
      for (IRInstr* elPTR : instrs) {
            delete elPTR;
      }
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, std::vector<std::string> params) {
      IRInstr* newInstr = new IRInstr(this, op, params);
      instrs.push_back(newInstr);
}

void BasicBlock::gen_asm(std::ostream &o) {
      o << label + ":\n";
      for(IRInstr* instr : instrs) {
            instr->gen_asm(o);
      }

      if(exit_true != nullptr) {
            if(exit_false != nullptr) {
                  o << "\tje " + exit_false->label << std::endl;
            }
            o << "\tjmp " + exit_true->label << std::endl;
      }
}