#pragma once
#include <memory>
#include "Expr.h"

struct PrintStmt;
struct ExprStmt;

struct StmtVisitor {
    virtual void visitPrintStmt(PrintStmt* stmt) = 0;
    virtual void visitExprStmt(ExprStmt* stmt) = 0;
    virtual void visitVarDecl(VarDecl* stmt) = 0;

};

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor* visitor) = 0;
};

struct VarDecl : Stmt {
    std::string name;
    std::unique_ptr<Expr> initializer;

    VarDecl(const std::string& n, std::unique_ptr<Expr> init)
        : name(n), initializer(std::move(init)) {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitVarDecl(this);
    }
};


struct PrintStmt : Stmt {
    std::unique_ptr<Expr> expression;

    PrintStmt(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitPrintStmt(this);
    }
};

struct ExprStmt : Stmt {
    std::unique_ptr<Expr> expression;

    ExprStmt(std::unique_ptr<Expr> expr)
        : expression(std::move(expr)) {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitExprStmt(this);
    }
};
