#pragma once

#include <vector>
#include <string>
#include <iostream>

class BasicBlock;

typedef enum {
      int64
} Type;

class IRInstr {
 
   public:
	/** The instructions themselves -- feel free to subclass instead */
	typedef enum {
		ldconst,
		copy,
		add,
		sub,
		mul,
		rmem,
		wmem,
		call, 
		cmp_eq,
		cmp_lt,
		cmp_le,
		push,
		pop,
		ret
	} Operation;

	/**  constructor */
	IRInstr(BasicBlock* bb_, Operation op, Type t, std::vector<std::string> params);
	IRInstr(BasicBlock* bb_, Operation op, std::vector<std::string> params);
	
	/** Actual code generation */
	void gen_asm(std::ostream &o); /**< x86 assembly code generation for this IR instruction */
	
 private:
	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	Operation op;
	Type t;
	std::vector<std::string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
	// if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design. 
};