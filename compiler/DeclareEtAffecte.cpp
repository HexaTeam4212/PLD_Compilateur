#include "DeclareEtAffecte.h"

DeclareEtAffecte::DeclareEtAffecte(Declaration* dec, Affectation* affec)
: declaration(dec), affectation(affec)
{}

DeclareEtAffecte::~DeclareEtAffecte() {
      delete declaration;
      delete affectation;
}

std::string DeclareEtAffecte::buildIR(CFG *cfg) {
      declaration->buildIR(cfg);
      return affectation->buildIR(cfg);
}

void DeclareEtAffecte::printInstruction(std::ostream &o, int shift) {
      declaration->printInstruction(o, shift);
      affectation->printInstruction(o, shift);
}

void DeclareEtAffecte::checkVariableUsage(std::map<std::string, int>* symbolTableNames, std::string functionName) {
      declaration->checkVariableUsage(symbolTableNames, functionName);
      affectation->checkVariableUsage(symbolTableNames, functionName);
}