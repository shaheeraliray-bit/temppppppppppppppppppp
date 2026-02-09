#pragma once
#include <string>
#include <vector>
#include "Token.h"

class Lexer {
private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, const std::string& literal);
    char peek();
    char peekNext();
    bool match(char expected);
    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
    void scanToken();
    void number();
    void identifier();
    void string();
    TokenType identifierType(const std::string& text);

public:
    Lexer(const std::string& s) : source(s) {}
    std::vector<Token> scanTokens();
};