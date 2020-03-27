//
//  BasicBlock.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>
#include <vector>
#include <iostream>

#include "CFG.h"
#include "IRInstr.h"

/** Class that represents a sequence of instructions that begins with a label
 *  and ends either with one jump, or two conditional jumps
 */
class BasicBlock {

public:
	// Constructor
	BasicBlock(CFG* cfg, std::string entry_label);
	// Destructor
	~BasicBlock();

	// write label and then all instructions
	// x86 assembly code generation for this basic block (very simple)
	void gen_asm(std::ostream &o);

	// Method to add an IR instruction
	void add_IRInstr(IRInstr::Operation op, Type t, std::vector<std::string> params);
	void add_IRInstr(IRInstr::Operation op, std::vector<std::string> params);

	// No encapsulation whatsoever here. Feel free to do better.
	/** pointer to the next basic block, true branch.
	 *  If nullptr, return from procedure
	 */
	BasicBlock* exit_true;
	/** pointer to the next basic block, false branch.
	 *  If null_ptr, the basic block ends with an unconditional jump
	 */
	BasicBlock* exit_false;
	// label of the BB, also will be the label in the generated code
	std::string label;
	// the CFG where this block belongs
	CFG* cfg;
	std::string test_var_name;

private:
	// the instructions themselves.
	std::vector<IRInstr*> instrs;
};