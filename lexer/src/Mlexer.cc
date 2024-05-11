#include "Mlexer.h"

MLexer::MLexer(std::string_view input) : Lexer(input) {}

Token MLexer::nextToken() {
    // 实现更具体的逻辑，可能覆盖 Lexer 类的 nextToken
    return Lexer::nextToken(); // 调用基类的实现，或者提供新的实现
}
