#pragma once

#include <string>
#include <iostream>

class CFG;

/**
 * Abstract class that represent instruction inside a function 
 */
class Instruction {

public:
      Instruction();
      ~Instruction();

      virtual std::string buildIR(CFG *cfg) = 0;
      virtual void printInstruction(std::ostream &o) = 0;
	  //virtual std::string getValue() = 0;
};