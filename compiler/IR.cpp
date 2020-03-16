#include "IR.h"

// IRInstr

IRInstr::IRInstr(BasicBlock* bb_, Operation op, Type t, std::vector<std::string> params)
    : bb(bb_), op(op), t(t), params(params)
{}

void IRInstr::gen_asm(std::ostream &o)
{
    switch (op)
    {
    case copy:
        o << "\tmovl " + params.at(0) + ", " + params.at(1) + "\n";
        break;
    
    default:
        break;
    }
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

CFG::CFG(ExprReturn* ast)
    : ast(ast)
{
    BasicBlock* entrypoint = new BasicBlock(this, "main");
    BasicBlock* exitpoint = new BasicBlock(this, "end");
    entrypoint->exit_true = exitpoint;
    current_bb = entrypoint;
    ast->buildIR(this);
}

void CFG::add_bb(BasicBlock* bb)
{
    bbs.push_back(bb);
}

void CFG::gen_asm(std::ostream &o)
{
    gen_asm_prologue(o);
    o << current_bb->label + ":\n";
    current_bb->gen_asm(o);
    gen_asm_epilogue(o);
}

std::string CFG::IR_reg_to_asm(std::string reg)
{
	return "";
}

void CFG::gen_asm_prologue(std::ostream &o)
{
    o << ".globl main\n";
}

void CFG::gen_asm_epilogue(std::ostream &o)
{
    o << "\tret\n";
}

void CFG::add_to_symbol_table(std::string name, IRInstr::Type t)
{
    //SymbolType.insert(name, t);
}

std::string CFG::create_new_tempvar(IRInstr::Type t)
{
	return "";
}

int CFG::get_var_index(std::string name)
{
	return -1;
}

IRInstr::Type CFG::get_var_type(std::string name)
{
	return IRInstr::Type::int64;
}

std::string CFG::new_BB_name()
{
	return "";
}