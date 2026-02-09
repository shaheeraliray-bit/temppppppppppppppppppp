#pragma once
#include <string>
#include <vector>
#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    void scanToken();
    char advance();
    bool isAtEnd();

    void number();
    void identifier();
    TokenType identifierType(const std::string& text);
};
