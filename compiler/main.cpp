//
//  main.cpp
//  PLD-COMP
//
//  Created by H4212 on 02/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ostream>
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
      std::string fileName = "";

      if (argn < 2) {
            std::cout << "Error : not enough argument" << std::endl;
            std::cout << "Syntax : ifcc [-p] [-o outfile] <PATH_TO_FILE>" << std::endl;
            return -3;
      }
      else if(argn >= 2) {
            for(int i = 1; i < argn-1; i++) {
                  if(strcmp("-p", argv[i]) == 0) {
                        printAST = true;
                  }
                  else if(strcmp("-o", argv[i]) == 0) {
                        if(i < argn-2 && argv[i+1][0] != '-') {
                              fileName = argv[++i];
                        }
                        else {
                              std::cout << "Error : parameter \"" << argv[i] << "\" need the name of the output file" << std::endl;
                              return -4;
                        }
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

            //Select output stream based on passed params
            std::streambuf* buffer;
            std::ofstream outputFile;
            if(strcmp(fileName.c_str(), "") != 0) {
                  outputFile.open(fileName,  std::ios::out | std::ios::trunc);
                  buffer = outputFile.rdbuf();
            }
            else {
                  buffer = std::cout.rdbuf();
            }
            std::ostream out(buffer);

            //Generate asembly in the correct output stream
            for(auto pCFG : listeCFG) {
                  pCFG->gen_asm(out);
            }
		
            delete ast;
            for(auto pCFG : listeCFG) {
                  delete pCFG;
            }
      }
      catch (std::invalid_argument e) {
            std::cout << "Error during file parsing" << std::endl;
            std::cout << e.what() << std::endl;
            return -1;
      }

      return 0;
}