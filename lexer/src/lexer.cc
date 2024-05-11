// lexer.cc
#include "lexer.h"
#include <cctype>

Lexer::Lexer(std::string_view input) : source(input), currentPos(0), currentLine(1), currentColumn(1) {
    operatorMap = {
        {"+", TokenType::POS},
        {"-", TokenType::NEG},
        {".", TokenType::DOT}, // Add DOT
        {"if", TokenType::IF},  // Add IF
        {"else", TokenType::ELSE}, // Add ELSE
        {"=", TokenType::EQ}, // Add EQ
        {"<", TokenType::LT}, // Add LT
        {"<=", TokenType::LE}, // Add LE
        {">", TokenType::GT}, // Add GT
        {">=", TokenType::GE}, // Add GE
        {"==", TokenType::DE}, // Add DE
    };
}

Token Lexer::nextToken() {
    if (peek() == '\0') {
        return Token(TokenType::END, "", currentLine, currentColumn); // End of file
    }

    skipWhitespace();

    int tokenStartLine = currentLine;
    int tokenStartColumn = currentColumn; // Ensure column is correctly captured at token start

    char next = peek();
    if (std::isdigit(next)) {
        return readNumber();
    } else if (std::isalpha(next) || next == '_') {
        return readIdentifierOrKeyword();
    } else if (next == '"') {
        return readStringLiteral();
    } else if (next == '/' && peek(1) == '/') {
        return skipComment();
    } else if (std::ispunct(next)) {
        return readOperator();
    } else {
        // Log error or handle unrecognized character
        getChar(); // Move past unrecognized character
        return Token(TokenType::UNKNOWN, std::string(1, next), tokenStartLine, tokenStartColumn);
    }
}


Token Lexer::readStringLiteral() {
    std::string value;
    getChar(); // Consume the initial quote
    while (peek() != '"' && peek() != '\0') {
        if (peek() == '\\') {  // Handle escape sequences
            getChar(); // Consume the backslash
            char escaped = getChar();
            switch (escaped) {
                case 'n': value += '\n'; break;
                case 't': value += '\t'; break;
                default: value += escaped;
            }
        } else {
            value += getChar();
        }
    }
    getChar(); // Consume the closing quote
    return Token(TokenType::STRING, value, currentLine, currentColumn);
}

Token Lexer::skipComment() {
    while (peek() != '\n' && peek() != '\0') {
        getChar();
    }
    return nextToken();  // Continue with the next token after the comment
}

char Lexer::peek(int offset) const {
    return currentPos + offset < source.length() ? source[currentPos + offset] : '\0';
}

char Lexer::getChar() {
    if (currentPos < source.length()) {
        char c = source[currentPos++];
        if (c == '\n') {
            currentLine++;
            currentColumn = 1; // Reset column to start for the new line
        } else {
            currentColumn++; // Increment column for the same line
        }
        return c;
    }
    return '\0'; // End of file or out of bounds
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) {
        getChar(); 
    }
}

Token Lexer::readNumber() {
    std::string value;
    int state = 0; // Initial state for integer part
    bool hasDecimal = false, hasExponent = false;
    int startColumn = currentColumn;
    std::string lastValidNum; // To store the last valid number before encountering non-valid
    int lastValidPos = currentPos; // To record the position of last valid number

    while (true) {
        char next = peek();
        switch (state) {
            case 0: // Initial integer state
                if (std::isdigit(next)) {
                    value += getChar();
                    lastValidNum = value;
                    lastValidPos = currentPos;
                } else if (next == '.') {
                    state = 1; // Switch to decimal state
                    value += getChar();
                    hasDecimal = true;
                } else if (next == 'E' || next == 'e') {
                    state = 2; // Switch to exponent part
                    value += getChar();
                    hasExponent = true;
                } else {
                    if (!hasExponent && !hasDecimal) {
                        return Token(TokenType::INT, value, currentLine, startColumn);
                    }
                    currentPos = lastValidPos; // Reset to last valid number position
                    return Token(TokenType::REAL, lastValidNum, currentLine, startColumn);
                }
                break;
            case 1: // Decimal numbers state
                if (std::isdigit(next)) {
                    value += getChar();
                    lastValidNum = value;
                    lastValidPos = currentPos;
                } else if (next == 'E' || next == 'e') {
                    state = 2; // Switch to exponent state
                    value += getChar();
                    hasExponent = true;
                } else {
                    currentPos = lastValidPos; // Reset to last valid number position
                    return Token(TokenType::REAL, lastValidNum, currentLine, startColumn);
                }
                break;
            case 2: // Exponent part may follow by + or -
                if (next == '+' || next == '-') {
                    value += getChar(); // Consume the sign
                    state = 3; // Move to final part of exponent
                } else if (std::isdigit(next)) {
                    value += getChar();
                    lastValidNum = value;
                    lastValidPos = currentPos;
                    state = 3; // Numbers after E or e
                } else {
                    currentPos = lastValidPos; // Reset to last valid number position
                    return Token(TokenType::REAL, lastValidNum, currentLine, startColumn);
                }
                break;
            case 3: // Handling the digits after the exponent sign
                if (std::isdigit(next)) {
                    value += getChar();
                    lastValidNum = value;
                    lastValidPos = currentPos;
                } else {
                    currentPos = lastValidPos; // Reset to last valid number position
                    return Token(TokenType::SCI, lastValidNum, currentLine, startColumn);
                }
                break;
            default:
                std::cerr << "Unreachable state in readNumber()" << std::endl;
                return Token(TokenType::UNKNOWN, "", currentLine, currentColumn);
        }
    }
}


Token Lexer::readIdentifierOrKeyword() {
    std::string value;
    while (std::isalnum(peek()) || peek() == '_') {
        value += getChar();
    }
    TokenType type = keywordTable.getTokenType(value);
    return Token(type, value, currentLine, currentColumn);
}

Token Lexer::readOperator() {
    std::string value = std::string(1, getChar());  // Start with the first character
    while (true) {
        char next = peek();
        if (next == '=' && (value == "<" || value == ">" || value == "!" || value == "=")) {
            value += getChar();  // Consume '=' to complete operators like '==', '<=', etc.
        } else {
            break;
        }
    }
    auto it = operatorMap.find(value);
    if (it != operatorMap.end()) {
        return Token(it->second, value, currentLine, currentColumn);
    } else {
        std::cerr << "Unrecognized operator: " << value << std::endl;
        return Token(TokenType::UNKNOWN, value, currentLine, currentColumn);
    }
}
