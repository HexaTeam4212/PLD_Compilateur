//
//  Function.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Function.h"

Function::Function()
{}

Function::~Function() {
      for (Instruction* instrPTR : instructions) {
            delete instrPTR;
      }
}

void Function::setName(std::string _name) {
      this->name = _name;
}

void Function::setReturnType(std::string _returnType) {
      this->returnType = _returnType;
}

void Function::setInstructions(std::vector<Instruction*> _vectInstr) {
      this->instructions = _vectInstr;
}

void Function::printFunction(std::ostream &o) {
      o << "\tFunction " << name << std::endl;
      o << "\tReturn : " << returnType << std::endl;
      o << "\tInstructions :" << std::endl;
      for(int i = 0; i < instructions.size(); i++) {
            instructions.at(i)->printInstruction(o);
      }
}