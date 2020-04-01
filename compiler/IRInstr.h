//
//  IRInstr.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <vector>
#include <string>
#include <iostream>

class BasicBlock;

typedef enum {
      int64
} Type;

/** 
 * Class which represents an IR instruction
 */
class IRInstr {
 
   public:
	/** The instructions themselves -- feel free to subclass instead */
	typedef enum {
		push,
		pop,
		movq,
		exit,
		ldconst,
		ret,
		copy,
		add,
		mult,
		diff,
		div,
		jpdeb,
		jpfin
	} Operation;

	//  Constructors
	IRInstr(BasicBlock* bb_, Operation op, Type t, std::vector<std::string> params);
	IRInstr(BasicBlock* bb_, Operation op, std::vector<std::string> params);
	
	// Actual code generation
	// x86 assembly code generation for this IR instruction
	void gen_asm(std::ostream &o);
	
 private:
 	/** The BB this instruction belongs to, 
	 * which provides a pointer to the CFG this instruction belong to
	 */
	BasicBlock* bb;
	Operation op;
	Type t;
	/** For 3-op instrs: d, x, y; for ldconst: d, c;
	 * For call: label, d, params;  for wmem and rmem: choose yourself
	 */
	std::vector<std::string> params;
	/** if you subclass IRInstr, each IRInstr subclass has its parameters and the
	 * previous (very important) comment becomes useless: it would be a better design.
	 */
};