#include "CFG.h"

#include <iostream>
#include <fstream>

CFG::CFG(Function* ast)
{
      nextBBnumber = 0;
      nextTempVarNumber = 1;
      initTableVariable();
      BasicBlock* prologue = gen_prologue(ast->getName());
      BasicBlock* base = new BasicBlock(this, new_BB_name());
      BasicBlock* epilogue = gen_epilogue(ast->getName());
      prologue->exit_true = base;
      base->exit_true = epilogue;
      current_bb = base;
      CFGStart = prologue;

      for(auto instr : ast->getInstructions()) {
            instr->buildIR(this);
      }
}

std::string CFG::new_BB_name() {
      std::string name("BB"+ std::to_string(nextBBnumber));
      ++nextBBnumber;
      return name;
}

BasicBlock* CFG::gen_prologue(std::string functionName) {
      BasicBlock* prologue = new BasicBlock(this, functionName);
      
      std::vector<std::string> paramsPushRbp;
      paramsPushRbp.push_back("%rbp");
      prologue->add_IRInstr(IRInstr::Operation::push, paramsPushRbp);

      std::vector<std::string> paramsMovRbpRsp;
      paramsMovRbpRsp.push_back("%rsp");
      paramsMovRbpRsp.push_back("%rbp");
      prologue->add_IRInstr(IRInstr::Operation::movq, paramsMovRbpRsp);

      return prologue;
}

BasicBlock* CFG::gen_epilogue(std::string functionName) {
      BasicBlock* epilogue = new BasicBlock(this, "end"+functionName);

      std::vector<std::string> paramsPopRbp;
      paramsPopRbp.push_back("%rbp");
      epilogue->add_IRInstr(IRInstr::Operation::pop, paramsPopRbp);

      std::vector<std::string> paramsRet;
      epilogue->add_IRInstr(IRInstr::Operation::exit, paramsRet);

      return epilogue;
}

void CFG::gen_asm(std::ostream &o) {

      current_bb = CFGStart;

      o << ".text\n";
      o << ".global main\n";

      while(current_bb != nullptr) {
            current_bb->gen_asm(o);

            if(current_bb->exit_true != nullptr && current_bb->exit_false != nullptr) {
                  //conditionnal jump
                  std::cout << "Conditional jump not handle" << std::endl;
                  current_bb = nullptr;
            }
            else {
                  current_bb = current_bb->exit_true;
            }
      }
}

IRVariable* CFG::getVariable(std::string nomVar) {
      return mapVariable.at(nomVar);
}

/**
 * Next, allocate local variables by making space on the stack. Recall, the stack grows down, 
 * so to make space on the top of the stack, the stack pointer should be decremented. 
 * The amount by which the stack pointer is decremented depends on the number and size of local variables needed. 
 * For example, if 3 local integers (4 bytes each) were required, the stack pointer would need to be decremented by 
 * 12 to make space for these local variables (i.e., sub esp, 12). 
 * As with parameters, local variables will be located at known offsets from the base pointer.
 */
// Here we used 64 bits integer so offset is 8 bytes instead of 4
int CFG::initTableVariable() {
      int sizeAllocate = 0;

      std::vector<Instruction*> instructions = ast->getInstructions();
      for(Instruction* instr : instructions) {

            //check if current instruction is a declaration
            if(dynamic_cast<Declaration*>(instr)) {
                  Declaration* dec = (Declaration*)instr;
                  Type type;
                  
                  if(dec->getType() == "int"){ type = Type::int64;}
                  sizeAllocate += getOffsetBaseOnType(type);

                  for(ExprVariable* exprVar : dec->getVarsDeclared()) {
                        IRVariable *var = new IRVariable(exprVar->getName(), type, sizeAllocate);
                        this->mapVariable.insert(std::pair<std::string, IRVariable*>(exprVar->getName(), var));
                  }
            }
            else {
                  break; //all declaration are put before any other instructions
            }
      }

      this->sizeAllocated = sizeAllocate;

      return sizeAllocate;
}

int CFG::getOffsetBaseOnType(Type type) {
      int offsetSize;
      switch (type)
      {
      case Type::int64 :
            offsetSize = 8;
            break;
      
      default:
            offsetSize = 0;
            break;
      }
      return offsetSize;
}

std::string CFG::create_new_tempvar(Type type) {
      std::string varName = "!tmp" + std::to_string(nextTempVarNumber);
      this->sizeAllocated += getOffsetBaseOnType(type);
      mapVariable.insert(std::pair<std::string, IRVariable*>(varName, new IRVariable(varName, type, this->sizeAllocated)));
      nextTempVarNumber++;

      return varName;
}