#include "token.h"

std::unordered_map<TokenType, int> tokenTypeMap = {
    {TokenType::END, 0},
    {TokenType::UNKNOWN, 1},
    {TokenType::DOT, 2},
    {TokenType::POS, 3},
    {TokenType::NEG, 4},
    {TokenType::IF, 5},
    {TokenType::ELSE, 6},
    {TokenType::ID, 7},
    {TokenType::INT, 8},
    {TokenType::WS, 9},
    {TokenType::EQ, 10},
    {TokenType::LT, 11},
    {TokenType::LE, 12},
    {TokenType::GT, 13},
    {TokenType::GE, 14},
    {TokenType::DE, 15},
    {TokenType::REAL, 16},
    {TokenType::SCI, 17}
};

Token::Token(TokenType type, std::string value, int line, int column)
    : type(type), value(value), line(line), column(column) {}

int Token::getLine() const {
    return line;
}

int Token::getColumn() const {
    return column;
}

TokenType Token::getType() const
{
    return type;
}

std::string Token::getValue() const
{
    return value;
}