//
//  CFG.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "CFG.h"

#include <iostream>
#include <fstream>

int CFG::nextBBnumber = 0;
std::map<std::string, Function*> CFG::mapFunction = {};

CFG::CFG(Function* ast)
: ast(ast)
{
	add_Function(ast);
      nextTempVarNumber = 1;
      initSymbolTable();
      BasicBlock* prologue = gen_prologue(ast->getName());
      add_basicblock(prologue);
      BasicBlock* base = new BasicBlock(this, new_BB_name());
      add_basicblock(base);
      BasicBlock* epilogue = gen_epilogue(ast->getName());
      prologue->exit_true = base;
	  
      base->exit_true = epilogue;
      current_bb = base;
      CFGEnd = epilogue;

      for(auto instr : ast->getInstructions()) {
            instr->buildIR(this);
      }
	  
      std::vector<std::string> params;
      params.push_back(std::to_string(sizeAllocated));
      prologue->add_IRInstr(IRInstr::Operation::jpdeb, params);

      delete epilogue;
      epilogue = gen_epilogue(ast->getName());
      current_bb->exit_true = epilogue;

      add_basicblock(epilogue);
}

CFG::~CFG() {
      delete ast;
      for(BasicBlock* bbPTR : allBBs) {
            delete bbPTR;
      }
      std::map<std::string, IRVariable*>::iterator it;
      for(it = symbolTable.begin(); it != symbolTable.end(); it++) {
            delete it->second;
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

	  
	  std::vector<std::string> params;
	  params.push_back(std::to_string(sizeAllocated));
	  epilogue->add_IRInstr(IRInstr::Operation::jpfin, params);

      std::vector<std::string> paramsPopRbp;
      paramsPopRbp.push_back("%rbp");
      epilogue->add_IRInstr(IRInstr::Operation::pop, paramsPopRbp);

      std::vector<std::string> paramsRet;
      epilogue->add_IRInstr(IRInstr::Operation::exit, paramsRet);

      return epilogue;
}

void CFG::gen_asm(std::ostream &o) {
      o << ".text\n";
      o << ".global " + ast->getName() + "\n";

      for(BasicBlock* bbPTR : allBBs) {
            bbPTR->gen_asm(o);
      }

}

IRVariable* CFG::getVariable(std::string nomVar) {
      return symbolTable.at(nomVar);
}

Function* CFG::getFunction(std::string nomFunction) {
	return mapFunction.at(nomFunction);
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
int CFG::initSymbolTable() {
	int sizeAllocate = 0;

	std::vector<Instruction*> instructions = ast->getInstructions();
	for (Instruction* instr : instructions) {

		//check if current instruction is a declaration
		if (dynamic_cast<Declaration*>(instr)) {
			Declaration* dec = (Declaration*)instr;
			Type type;

			if (dec->getType() == "int") { type = Type::int64; }

			for (ExprVariable* exprVar : dec->getVarsDeclared()) {
				sizeAllocate += getOffsetBaseOnType(type);
				IRVariable *var = new IRVariable(exprVar->getName(), type, sizeAllocate);
				this->symbolTable.insert(std::pair<std::string, IRVariable*>(exprVar->getName(), var));
			}
		}
		else if (dynamic_cast<DeclarationArg*>(instr)) {

			DeclarationArg* decArg = (DeclarationArg*)instr;
			Type type;
			std::vector<std::string> varsType=decArg->getVarsType();
			std::vector<std::string>::iterator it= varsType.begin();
			type = Type::int64;

			for (ExprVariable* exprVar : decArg->getVarsDeclared()) {
				if (*it == "int") { type = Type::int64; }
				sizeAllocate += getOffsetBaseOnType(type);
				IRVariable *var = new IRVariable(exprVar->getName(), type, sizeAllocate);
				this->symbolTable.insert(std::pair<std::string, IRVariable*>(exprVar->getName(), var));
				if (it != varsType.end()) {
					++it;
				}
			}
		}
            else if (dynamic_cast<DeclareEtAffecte*>(instr)) {
                  DeclareEtAffecte* decEtAffec = (DeclareEtAffecte*) instr;
                  Type type;

                  if(decEtAffec->getDeclaration()->getType() == "int") { type = Type::int64; }

                  for (ExprVariable* exprVar : decEtAffec->getDeclaration()->getVarsDeclared()) {
                        sizeAllocate += getOffsetBaseOnType(type);
				IRVariable *var = new IRVariable(exprVar->getName(), type, sizeAllocate);
				this->symbolTable.insert(std::pair<std::string, IRVariable*>(exprVar->getName(), var));
                  }
            }
		else 
		{
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
      symbolTable.insert(std::pair<std::string, IRVariable*>(varName, new IRVariable(varName, type, this->sizeAllocated)));
      nextTempVarNumber++;

      return varName;
}

std::string CFG::add_Function(Function* function) {
	mapFunction.insert(std::pair<std::string, Function*>(function->getName(), function));
	return function->getName();
}

void CFG::add_basicblock(BasicBlock* newBB) {
      allBBs.push_back(newBB);
}