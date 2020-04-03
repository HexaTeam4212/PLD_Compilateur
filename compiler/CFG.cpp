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
std::vector<std::string> CFG::registres = {"%edi","%esi","%edx","%ecx","%r8d","r9d" };

CFG::CFG(Function* ast)
: ast(ast)
{
      
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
	  
	  std::vector<std::string> params;
	  params.push_back(std::to_string(sizeAllocated));
	  prologue->add_IRInstr(IRInstr::Operation::jpdeb, params);
	  epilogue= gen_epilogue(ast->getName());
	  base->exit_true = epilogue;
}

CFG::~CFG() {
      delete ast;
      delete CFGStart;
      std::map<std::string, IRVariable*>::iterator it;
      for(it = mapVariable.begin(); it != mapVariable.end(); it++) {
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
      std::cout << "gen prologue" << std::endl;
      std::vector<std::string> paramsPushRbp;
      paramsPushRbp.push_back("%rbp");
      prologue->add_IRInstr(IRInstr::Operation::push, paramsPushRbp);

      std::vector<std::string> paramsMovRbpRsp;
      paramsMovRbpRsp.push_back("%rsp");
      paramsMovRbpRsp.push_back("%rbp");
      prologue->add_IRInstr(IRInstr::Operation::movq, paramsMovRbpRsp);

	  // ajout des argument
	  std::cout << "je suis ici" << std::endl;
	  std::cout << functionName << std::endl;
	  /*Function* function = getFunction(functionName);
	  
	  std::vector<ExprVariable*> argumentFonction=function->getArguments();
	  
	  std::cout << "ivi" << std::endl;

	  for (int i = 1; i < argumentFonction.size(); i++) {
		  
		  std::vector<std::string> paramsfonction;
		  paramsfonction.push_back(registres.at(i));
		  std::string argName=argumentFonction.at(i)->getName();
		  IRVariable* varArgumenti = getVariable(argName);
		  paramsfonction.push_back(std::to_string(varArgumenti->getOffset()));
	      prologue->add_IRInstr(IRInstr::Operation::movq, paramsfonction);
	  }*/
	  
	  std::cout << "fin gen prologue" << std::endl;
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

Function* CFG::getFunction(std::string nomFunction) {
	std::cout << "getFunction" << std::endl;
	//deque<Function*>::iterator it;
	for (std::map<std::string, Function*>::iterator it = mapFunction.begin(); it != mapFunction.end(); ++it)
	{
		std::cout << it->first << std::endl;   
	}
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
int CFG::initTableVariable() {
	int sizeAllocate = 0;

	std::vector<Instruction*> instructions = ast->getInstructions();
	for (Instruction* instr : instructions) {

		//check if current instruction is a declaration
		if (dynamic_cast<Declaration*>(instr)) {
			std::cout << "tiiiiiiiiiiiiiiiii" << std::endl;
			Declaration* dec = (Declaration*)instr;
			Type type;

			if (dec->getType() == "int") { type = Type::int64; }

			for (ExprVariable* exprVar : dec->getVarsDeclared()) {
				sizeAllocate += getOffsetBaseOnType(type);
				IRVariable *var = new IRVariable(exprVar->getName(), type, sizeAllocate);
				this->mapVariable.insert(std::pair<std::string, IRVariable*>(exprVar->getName(), var));
			}
		}
		else if (dynamic_cast<Function*>(instr)) {
			Function* function = (Function*)instr;
			std::cout << "tututuututu" << function->getName() << std::endl;

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
      mapVariable.insert(std::pair<std::string, IRVariable*>(varName, new IRVariable(varName, type, this->sizeAllocated)));
      nextTempVarNumber++;

      return varName;
}

std::string CFG::add_Function(Function* function) {
	std::cout << "add Function _-_-_-_-_-_ 55555" << std::endl;
	std::cout << function->getName() << std::endl;
	mapFunction.insert(std::pair<std::string, Function*>(function->getName(), function));
	return function->getName();
}