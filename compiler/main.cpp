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
#include "ParserErrorListener.h"

int main(int argn, const char **argv) {
      std::stringstream in;
      if (argn==2) {
            std::ifstream lecture(argv[1]);
            in << lecture.rdbuf();
      }

      antlr4::ANTLRInputStream input(in.str());
      ifccLexer lexer(&input);
      antlr4::CommonTokenStream tokens(&lexer);
      ifccParser parser(&tokens);
      
      //Add listener for error detection
      parser.removeErrorListeners();
      ParserErrorListener errorListener;
      parser.addErrorListener(&errorListener);

      //tokens.fill();
      //for(auto token : tokens.getTokens()) {
      //      std::cout << token->toString() << std::endl;
      //}

      try {
            antlr4::tree::ParseTree* tree = parser.axiom();

            Visitor visitor;
            Program* ast = (Program*) visitor.visit(tree);

            //IR generation
            std::vector<CFG*> listeCFG;

            for(auto pFunction : ast->getAllFunctions()) {
                  CFG *newCfg = new CFG(pFunction);
                  listeCFG.push_back(newCfg);
            }

            //Generate Assembly code
            for(auto pCFG : listeCFG) {
                  pCFG->gen_asm(std::cout);
            }
      }
      catch (std::invalid_argument e) {
            std::cout << "Error during file parsing" << std::endl;
            std::cout << e.what() << std::endl;
            return -1;
      }

      return 0;
}