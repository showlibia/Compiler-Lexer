#include <fstream>
#include <sstream>
#include "gtest/gtest.h"
#include "Mlexer.h"

class MLexerFileTest : public ::testing::Test {
protected:
    std::string readInputFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

void printToken(const Token& token, std::ofstream& outputFile) {
    int typeCode = tokenTypeMap[token.getType()];  // 获取Token类型的整数代码
    outputFile << "[@-1," << token.getColumn() - 1 << ":" << token.getColumn() + token.getValue().length() - 1
               << "='" << token.getValue() << "',<" << typeCode << ">,"
               << token.getLine() << ":" << token.getColumn() - 1 << "]" << std::endl;
}

TEST_F(MLexerFileTest, TokenizesDragon0Txt) {
    std::string input = readInputFromFile("../dragon0.txt");  // 确保路径正确
    MLexer lexer(input);
    Token token(TokenType::UNKNOWN, "", 0, 0);

    std::ofstream outputFile("../output_tokens.txt");  // 创建文件流对象
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    do {
        token = lexer.nextToken();
        printToken(token, outputFile);  // 将输出写入文件
    } while (token.getType() != TokenType::END);

    outputFile.close();  // 关闭文件流
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
