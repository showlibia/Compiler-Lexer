#ifndef M_LEXER_H
#define M_LEXER_H

#include "lexer.h"

class MLexer : public Lexer {
public:
    MLexer(std::string_view input);
    Token nextToken();
    // 可能还有其他特化方法
};

#endif // M_LEXER_H
