//
//  DeclareEtAffecte.h
//  PLD-COMP
//
//  Created by H4212 on 07/04/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

class Affectation;
class Declaration;

#include "Instruction.h"
#include "CFG.h"

class DeclareEtAffecte : public Instruction {

public:
      DeclareEtAffecte(Declaration* dec, Affectation* affec);
      ~DeclareEtAffecte();

      std::string buildIR(CFG *cfg) override;
      void printInstruction(std::ostream &o, int shift) override;
      virtual void checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) override;

      Declaration* getDeclaration() {return declaration;};

private:
      Declaration* declaration;
      Affectation* affectation;
};