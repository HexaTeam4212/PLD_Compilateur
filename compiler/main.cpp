#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccVisitor.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "Program.h"
#include "visitor.h"
#include "CFG.h"
#include "ParserErrorListener.h"

int main(int argn, const char **argv) {
      std::stringstream in;
      bool printAST = false;

      if (argn < 2) {
            std::cout << "Error : not enough argument" << std::endl;
            std::cout << "Syntax : ifcc [-p] <PATH_TO_FILE>" << std::endl;
            return -3;
      }
      else if(argn >= 2) {
            for(int i = 1; i < argn-1; i++) {
                  if(strcmp("-p", argv[i]) == 0) {
                        printAST = true;
                  }
                  else {
                        std::cout << "Error : parameter \"" << argv[i] << "\" doesn't exist" << std::endl;
                        return -2;
                  }
            }
            std::ifstream lecture(argv[argn-1]);
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

      try {
            antlr4::tree::ParseTree* tree = parser.axiom();

            Visitor visitor;
            Program* ast = (Program*) visitor.visit(tree);

            if(printAST) {
                  ast->printProgram(std::cout);
            }

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