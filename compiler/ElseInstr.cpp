#include "ElseInstr.h"

ElseInstr::ElseInstr() 
{}

ElseInstr::~ElseInstr() 
{}

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

void ElseInstr::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
      for(Instruction* instrPTR : vectorInstruction) {
            instrPTR->checkVariableUsage(mapVariableNames, functionName);
      }
}

void ElseInstr::addInstruction(Instruction* newInstruction) {
      vectorInstruction.push_back(newInstruction);
}
