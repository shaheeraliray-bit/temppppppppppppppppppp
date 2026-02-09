#pragma once
#include "Token.h"
#include <memory>

struct Expr {
    virtual ~Expr() = default;
};

struct Literal : Expr {
    Token value;
    Literal(Token value) : value(value) {}
};

struct Grouping : Expr {
    std::unique_ptr<Expr> expression;
    Grouping(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}
};
