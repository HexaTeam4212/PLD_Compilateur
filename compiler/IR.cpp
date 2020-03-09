#include "IR.h"

// IRInstr

IRInstr::IRInstr(BasicBlock* bb_, Operation op, Type t, std::vector<std::string> params)
    : bb(bb_), op(op), t(t), params(params)
{}

void IRInstr::gen_asm(std::ostream &o)
{
    // do stuff in function off instr and parameters
}

// BasicBlock

BasicBlock::BasicBlock(CFG* cfg, std::string entry_label)
    : cfg(cfg), label(entry_label)
{}

void BasicBlock::gen_asm(std::ostream &o)
{
    for(int i = 0; i < instrs.size(); i++)
    {
        instrs.at(i)->gen_asm(o);
    }

    //do stuff when all instruction are processed
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, IRInstr::Type t, std::vector<std::string> params)
{
    IRInstr* newIRInstr = new IRInstr(this, op, t, params);
    instrs.push_back(newIRInstr);
}

// CFG

CFG::CFG(DefFonction* ast)
    : ast(ast)
{

}

void CFG::add_bb(BasicBlock* bb)
{
    bbs.push_back(bb);
}

void CFG::gen_asm(std::ostream &o)
{

}

std::string CFG::IR_reg_to_asm(std::string reg)
{

}

void CFG::gen_asm_prologue(std::ostream &o)
{

}

void CFG::gen_asm_epilogue(std::ostream &o)
{

}

void CFG::add_to_symbol_table(std::string name, IRInstr::Type t)
{
    //SymbolType.insert(name, t);
}

std::string CFG::create_new_tempvar(IRInstr::Type t)
{

}

int CFG::get_var_index(std::string name)
{

}

IRInstr::Type CFG::get_var_type(std::string name)
{

}

std::string CFG::new_BB_name()
{

}