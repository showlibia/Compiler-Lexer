#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <unordered_map>

enum class TokenType {
    // Group 0
    END, // end of file
    UNKNOWN, // for error

    // Group 1
    // lookhead = 1 (LA(1))
    DOT, // '.'
    POS, // '+'
    NEG, // '-'
    IF,  // 'if'
    ELSE,// 'else'
    STRING,
    ID,
    INT,
    WS,  // ' '

    // Group 2
    // =, ==, <, <=, >, >=
    // LA(2)
    EQ, // '='
    LT, // '<'
    LE, // '<='
    GT, // '>'
    GE, // '>='
    DE, // '=='

    // Group 3
    // arbitrary LA
    REAL,
    SCI,
};

extern std::unordered_map<TokenType, int> tokenTypeMap;

class Token {
public:
    Token(TokenType type, std::string value, int line, int column);

    TokenType getType() const;
    std::string getValue() const;
    int getLine() const;
    int getColumn() const;

private:
    TokenType type;
    std::string value;
    int line;
    int column;
};

#endif