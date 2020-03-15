#pragma once

#include <string>

class CFG;

/**
 * Abstract class that represent instruction inside a function 
 */
class Instruction {

public:
      Instruction();
      ~Instruction();

      virtual std::string buildIR(CFG *cfg) = 0;
};