#include <iostream>
#include <fstream>
#include <vector>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccVisitor.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "Program.h"
#include "Visitor.h"
#include "CFG.h"

int main(int argn, const char **argv) {
      std::stringstream in;
      if (argn==2) {
            std::ifstream lecture(argv[1]);
            in << lecture.rdbuf();
      }

      antlr4::ANTLRInputStream input(in.str());
      ifccLexer lexer(&input);
      antlr4::CommonTokenStream tokens(&lexer);
      
      tokens.fill();
      //for(auto token : tokens.getTokens()) {
      //      std::cout << token->toString() << std::endl;
      //}

      ifccParser parser(&tokens);
      antlr4::tree::ParseTree* tree = parser.axiom();

      Visitor visitor;
      Program* ast = (Program*) visitor.visit(tree);

      //IR generation
      std::vector<CFG*> listeCFG;

      for(auto pFunction : ast->getAllFunctions()) {
            CFG *newCfg = new CFG(pFunction);
            listeCFG.push_back(newCfg);
      }

      

      return 0;
}