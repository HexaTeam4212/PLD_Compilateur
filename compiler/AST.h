#pragma once

class CFG;

#include <string>
#include "IR.h"

class Expr 
{
public:
    Expr();
    virtual std::string buildIR(CFG* cfg) = 0;
};

class ExprConstant : public Expr
{
public:
    ExprConstant(std::string value);
    std::string buildIR(CFG* cfg);

private:
    std::string value;
};

class ExprReturn : public Expr
{
public:
    ExprReturn(Expr* to_return);
    std::string buildIR(CFG* cfg);

private:
    Expr* to_return;
};