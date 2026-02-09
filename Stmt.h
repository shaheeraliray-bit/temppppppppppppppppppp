#pragma once
#include <memory>
#include <string>
#include "Expr.h"

class VarDecl;
class ExprStmt;
class PrintStmt;

class StmtVisitor {
public:
    virtual ~StmtVisitor() = default;
    virtual void visitVarDecl(VarDecl* stmt) = 0;
    virtual void visitExprStmt(ExprStmt* stmt) = 0;
    virtual void visitPrintStmt(PrintStmt* stmt) = 0;
};

class Stmt {
public:
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor* visitor) = 0;
};

class VarDecl : public Stmt {
public:
    std::string name;
    std::unique_ptr<Expr> initializer;

    VarDecl(const std::string& n, std::unique_ptr<Expr> init) 
        : name(n), initializer(std::move(init)) {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitVarDecl(this);
    }
};

class ExprStmt : public Stmt {
public:
    std::unique_ptr<Expr> expression;

    ExprStmt(std::unique_ptr<Expr> expr) : expression(std::move(expr)) {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitExprStmt(this);
    }
};

class PrintStmt : public Stmt {
public:
    std::unique_ptr<Expr> expression;

    PrintStmt(std::unique_ptr<Expr> expr) : expression(std::move(expr)) {}

    void accept(StmtVisitor* visitor) override {
        visitor->visitPrintStmt(this);
    }
};