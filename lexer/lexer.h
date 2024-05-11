#ifndef LEXER_H
#define LEXER_H

#include <cstddef>
#include <string>
#include "keyword_table.h"
#include "token.h"
#include <iostream>


class Lexer {
private:
    std::string source;
    std::size_t currentPos;
    int currentLine;
    int currentColumn;
    KeywordTable keywordTable;
    std::unordered_map<std::string, TokenType> operatorMap;

    char peek(int offset = 0) const;
    char getChar();
    void skipWhitespace();
    Token readNumber();  
    Token readIdentifierOrKeyword();  
    Token readStringLiteral(); 
    Token skipComment();  
    Token readOperator(); 
public:
    Lexer(std::string_view input);
    Token nextToken();
};


#endif