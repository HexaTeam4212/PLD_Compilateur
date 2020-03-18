#include "IRVariable.h"

IRVariable::IRVariable(std::string name, Type type, int offset)
: name(name), varType(type), offset(offset)
{}

IRVariable::~IRVariable()
{}