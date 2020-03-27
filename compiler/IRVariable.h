//
//  IRVariable.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

// Interfaces used
#include <string>

#include "IRInstr.h"

/**
 * Class which represents an IR variable
 */
class IRVariable {

public:
      // Constructor
      IRVariable(std::string name, Type type, int offset);
      // Destructor
      ~IRVariable();

      // Getters
      std::string getName() { return name; };
      Type getVarType() { return varType; };
      int getOffset() { return offset; };

private:
      std::string name;
      Type varType;
      int offset;
};