#include "keyword_table.h"
#include "token.h"

KeywordTable::KeywordTable()
{
    keywordMap["if"] = TokenType::IF;
    keywordMap["else"] = TokenType::ELSE;
}

TokenType KeywordTable::getTokenType(std::string_view keyword) const
{
    auto it = keywordMap.find(std::string(keyword));
    if (it != keywordMap.end()) {
        return it->second;
    }
    return TokenType::ID;
}