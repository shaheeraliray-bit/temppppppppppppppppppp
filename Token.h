#pragma once
#include <string>

enum class TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    SEMICOLON,
    PLUS, MINUS, STAR, SLASH,
    EQUAL,

    // One or two character tokens
    EQUAL_EQUAL,
    BANG_EQUAL,
    LESS, GREATER,

    // Literals
    IDENTIFIER,
    NUMBER,
    STRING,
    // Keywords
      NETLANG_VAR,        
    NETLANG_PRINT,     
    NETLANG_IF,
    NETLANG_ELSE,
    NETLANG_WHILE,
    NETLANG_TRUE,
    NETLANG_FALSE,

    END_OF_FILE
};


struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, std::string lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {}
};
