#pragma once
#include "Token.h"
#include <memory>

struct Binary;
struct Literal;
struct Grouping;
struct Variable; 

struct ExprVisitor {
    virtual double visitBinary(Binary* expr) = 0;
    virtual double visitLiteral(Literal* expr) = 0;
    virtual double visitGrouping(Grouping* expr) = 0;
    virtual double visitVariable(Variable* expr) = 0;

};

struct Expr {
    virtual ~Expr() = default;
    virtual double accept(ExprVisitor* visitor) = 0;
};

struct Literal : Expr {
    Token value;
    Literal(Token value) : value(value) {}

    double accept(ExprVisitor* visitor) override {
        return visitor->visitLiteral(this);
    }
};

struct Binary : Expr {
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    double accept(ExprVisitor* visitor) override {
        return visitor->visitBinary(this);
    }
};

struct Grouping : Expr {
    std::unique_ptr<Expr> expression;
    Grouping(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}

    double accept(ExprVisitor* visitor) override {
        return visitor->visitGrouping(this);
    }
};

struct Variable : Expr {
    std::string name;
    Variable(const std::string& n) : name(n) {}

    double accept(ExprVisitor* visitor) override {
        return visitor->visitVariable(this);
    }
};
