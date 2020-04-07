#include "ElseInstr.h"

ElseInstr::ElseInstr() 
{}

ElseInstr::~ElseInstr() {
      for(Instruction* instrPTR : vectorInstruction) {
            delete instrPTR;
      }
}

std::string ElseInstr::buildIR(CFG *cfg) {
	for(Instruction* instr : vectorInstruction) {
            instr->buildIR(cfg);
      }
	  
    return "";
}

void ElseInstr::printInstruction(std::ostream &o, int shift) {
      o << std::string(shift, '\t') + "Else statement" << std::endl;
      o << std::string(shift, '\t') + "Instructions :" << std::endl;
      for(Instruction* instrPTR : vectorInstruction) {
            instrPTR->printInstruction(o, shift+1);
      }
}

void ElseInstr::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      for(Instruction* instrPTR : vectorInstruction) {
            instrPTR->checkVariableUsage(symbolTableNames, functionName);
      }
}

void ElseInstr::addInstruction(Instruction* newInstruction) {
      vectorInstruction.push_back(newInstruction);
}
