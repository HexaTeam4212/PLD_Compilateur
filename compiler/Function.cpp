//
//  Function.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "Function.h"
#include "CFG.h"

Function::Function(std::string returnType, std::string name, std::vector<ExprVariable*> arguments):
returnType(returnType), name(name), arguments(arguments)
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
std::string Function::buildIR(CFG *cfg) {
	return "";
}

void Function::printFunction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "Function " << name << std::endl;
      o << std::string(shift, '\t') + "Return : " << returnType << std::endl;
      o << std::string(shift, '\t') + "Instructions :" << std::endl;
      for(int i = 0; i < instructions.size(); i++) {
            instructions.at(i)->printInstruction(o, shift+1);
      }
}

void Function::checkVariables(std::map<std::string, int>* mapVariableNames) {
      for(int i = 0; i < instructions.size(); i++) {
            instructions.at(i)->checkVariableUsage(mapVariableNames, this->name);
      }
}