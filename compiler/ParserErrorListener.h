//
//  ParserErrorListener.h
//  PLD-COMP
//
//  Created by H4212 on 16/03/2020.
//  Copyright © 2020 Andrea Croc, Baptiste Lotigier, Emmy Lerandy, Fatoumata Wade,
//                   Louis Ung, Lucie Bovo, Shuyao Shen. All rights reserved.
//

#pragma once

#include <string>

#include "antlr4-runtime.h"

class ParserErrorListener : public antlr4::BaseErrorListener {

      void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token* offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override
      {
            std::string s = "Line(" + std::to_string((long)line) + ":" + std::to_string((long)charPositionInLine) + ") Error while parsing file : " + msg; 
            throw std::invalid_argument(s);
      }
};