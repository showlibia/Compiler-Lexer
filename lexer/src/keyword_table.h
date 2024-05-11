#ifndef KEYWORD_TABLE_H
#define KEYWORD_TABLE_H

#include <unordered_map>
#include <string>
#include "token.h"

class KeywordTable {
public:
    KeywordTable();
    TokenType getTokenType(std::string_view keyword) const;

private:
    std::unordered_map<std::string, TokenType> keywordMap;
};

#endif