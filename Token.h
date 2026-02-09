#pragma once
#include <string>

enum class TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    SEMICOLON,
    PLUS, MINUS, STAR, SLASH,PERCENT,
    EQUAL,COMMA, DOT,

    // One or two character tokens
    EQUAL_EQUAL,
    BANG_EQUAL,
    LESS, LESS_EQUAL, GREATER, GREATER_EQUAL,

    // Literals
    IDENTIFIER,
    NUMBER,
    STRING_LIT,
    // Keywords
      VAR,        
    LOGONCONSOLE,     
    IF,
    ELSE,
    WHILE,
    TRUE,
    FALSE,

    END_OF_FILE
};


struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType type, std::string lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {}
};
