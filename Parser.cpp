#include "Parser.h"
#include <iostream>

// ---------------- CONSTRUCTOR ----------------
Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens) {}

// ---------------- PARSE ALL STATEMENTS ----------------
std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;

    while (!isAtEnd()) {
        statements.push_back(statement());
    }

    return statements;
}

// ---------------- STATEMENTS ----------------
std::unique_ptr<Stmt> Parser::statement() {
    if (match(TokenType::NETLANG_PRINT)) {
        return printStatement();
    } else if (match(TokenType::NETLANG_VAR)) {
        return varDeclaration(); 
    } 
    return expressionStatement();
}

// Parse: logOnConsole(...)
std::unique_ptr<Stmt> Parser::printStatement() {
    if (!match(TokenType::LEFT_PAREN)) {
        std::cerr << "Expected '(' after print\n";
    }

    auto value = expression();

    if (!match(TokenType::RIGHT_PAREN)) {
        std::cerr << "Expected ')'\n";
    }

    if (!match(TokenType::SEMICOLON)) {
        std::cerr << "Expected ';'\n";
    }

    return std::make_unique<PrintStmt>(std::move(value));
}

// Parse: expression;
std::unique_ptr<Stmt> Parser::expressionStatement() {
    auto expr = expression();

    if (!match(TokenType::SEMICOLON)) {
        std::cerr << "Expected ';'\n";
    }

    return std::make_unique<ExprStmt>(std::move(expr));
}

// ---------------- VARIABLE DECLARATION ----------------
// parse: define x = expression;
std::unique_ptr<Stmt> Parser::varDeclaration() {
    if (!match(TokenType::IDENTIFIER)) {
        std::cerr << "Expected variable name after 'define'\n";
        return nullptr;
    }

    std::string varName = previous().lexeme;

    if (!match(TokenType::EQUAL)) {
        std::cerr << "Expected '=' after variable name\n";
        return nullptr;
    }

    auto initializer = expression();

    if (!match(TokenType::SEMICOLON)) {
        std::cerr << "Expected ';' after variable declaration\n";
        return nullptr;
    }

    return std::make_unique<VarDecl>(varName, std::move(initializer));
}

// ---------------- EXPRESSIONS ----------------
std::unique_ptr<Expr> Parser::expression() {
    return term();
}

std::unique_ptr<Expr> Parser::term() {
    auto expr = factor();

    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        Token op = previous();
        auto right = factor();
        expr = std::make_unique<Binary>(
            std::move(expr),
            op,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expr> Parser::factor() {
    if (match(TokenType::NUMBER)) {
        return std::make_unique<Literal>(previous());
    }

    if (match(TokenType::LEFT_PAREN)) {
        auto expr = expression();
        if (!match(TokenType::RIGHT_PAREN)) {
            std::cerr << "Expected ')'\n";
        }
        return std::make_unique<Grouping>(std::move(expr));
    }

    if (match(TokenType::IDENTIFIER)) {
        return std::make_unique<Variable>(previous().lexeme);
    }

    std::cerr << "Unexpected token: " << peek().lexeme << "\n";
    return nullptr;
}

// ---------------- HELPERS ----------------
bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}
