#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "Stmt.h"
#include "Expr.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);

    // Returns all statements in the program as a vector
    std::vector<std::unique_ptr<Stmt>> parse();

private:
    const std::vector<Token>& tokens;
    int current = 0;

    // ---------------- STATEMENTS ----------------
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> printStatement();
    std::unique_ptr<Stmt> expressionStatement();
    std::unique_ptr<Stmt> varDeclaration(); 

    // ---------------- EXPRESSIONS ----------------
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();

    // ---------------- HELPERS ----------------
    bool match(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
};
