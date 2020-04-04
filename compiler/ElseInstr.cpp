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

void ElseInstr::printInstruction(std::ostream &o) {}

void ElseInstr::checkVariableUsage(std::map<std::string, int>* mapVariableNames, std::string functionName) {
      for(Instruction* instrPTR : vectorInstruction) {
            instrPTR->checkVariableUsage(mapVariableNames, functionName);
      }
}

void ElseInstr::addInstruction(Instruction* newInstruction) {
      vectorInstruction.push_back(newInstruction);
}
