#include "Lexer.h"
#include <cctype>

// ---------------- Constructor ----------------

Lexer::Lexer(const std::string& source)
    : source(source) {}

// ---------------- Public API ----------------

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.emplace_back(TokenType::END_OF_FILE, "", line);
    return tokens;
}

// ---------------- Core Scanner ----------------

void Lexer::scanToken() {
    char c = advance();

    switch (c) {
        case '(':
            tokens.emplace_back(TokenType::LEFT_PAREN, "(", line);
            break;
        case ')':
            tokens.emplace_back(TokenType::RIGHT_PAREN, ")", line);
            break;
        case ';':
            tokens.emplace_back(TokenType::SEMICOLON, ";", line);
            break;
        case '+':
            tokens.emplace_back(TokenType::PLUS, "+", line);
            break;
        case '-':
            tokens.emplace_back(TokenType::MINUS, "-", line);
            break;
        case '"':
            string();
            break;
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        default:
            if (isdigit(c)) {
                number();
            } else if (isalpha(c) || c == '_') {
                identifier();
            }
            break;
    }
}

// ---------------- Helpers ----------------

char Lexer::advance() {
    return source[current++];
}

bool Lexer::isAtEnd() {
    return current >= source.length();
}

// ---------------- Token Builders ----------------

void Lexer::number() {
    while (!isAtEnd() && isdigit(source[current])) {
        advance();
    }

    std::string value = source.substr(start, current - start);
    tokens.emplace_back(TokenType::NUMBER, value, line);
}

TokenType Lexer::identifierType(const std::string& text) {
    if (text == "logOnConsole") return TokenType::PRINT;
    return TokenType::IDENTIFIER;
}

void Lexer::identifier() {
    while (!isAtEnd() && (isalnum(source[current]) || source[current] == '_')) {
        advance();
    }

    std::string text = source.substr(start, current - start);
    tokens.emplace_back(identifierType(text), text, line);
}
void Lexer::string() {
    while (!isAtEnd() && source[current] != '"') advance();
    if (isAtEnd()) {
        std::cerr << "Unterminated string at line " << line << "\n";
        return;
    }

    advance();
    std::string value = source.substr(start + 1, current - start - 2); // skip quotes
    tokens.emplace_back(TokenType::STRING, value, line);
}
