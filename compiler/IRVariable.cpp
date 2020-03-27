//
//  IRVariable.cpp
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include "IRVariable.h"

IRVariable::IRVariable(std::string name, Type type, int offset)
: name(name), varType(type), offset(offset)
{}

IRVariable::~IRVariable()
{}