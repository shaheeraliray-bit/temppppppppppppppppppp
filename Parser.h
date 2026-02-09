#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Stmt.h"
#include "Expr.h"

class Parser {
private:
    std::vector<Token> tokens;
    int current = 0;

    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> varDeclaration();
    std::unique_ptr<Stmt> printStatement();
    std::unique_ptr<Stmt> expressionStatement();
    
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> assignment();
    std::unique_ptr<Expr> logicalOr();
    std::unique_ptr<Expr> logicalAnd();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    Token peek() const;
    Token previous() const;
    Token advance();
    bool check(TokenType type) const;
    bool match(std::initializer_list<TokenType> types);
    bool isAtEnd() const;

public:
    Parser(const std::vector<Token>& t) : tokens(t) {}
    std::vector<std::unique_ptr<Stmt>> parse();
};