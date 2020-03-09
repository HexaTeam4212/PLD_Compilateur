#include "AST.h"

Expr::Expr()
{}

ExprConstant::ExprConstant(std::string value)
    : value(value)
{}

std::string ExprConstant::buildIR(CFG* cfg)
{
    return "$"+this->value;
}

ExprReturn::ExprReturn(Expr* to_return)
    : to_return(to_return)
{}

std::string ExprReturn::buildIR(CFG* cfg)
{
    std::string var_to_return = to_return->buildIR(cfg);
    std::vector<std::string> params;
    params.push_back(var_to_return);
    params.push_back("%eax");
    cfg->current_bb->add_IRInstr(IRInstr::Operation::copy, IRInstr::Type::int64, params);
    return "";
}