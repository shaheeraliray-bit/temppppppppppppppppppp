#pragma once
#include "Expr.h"
#include "Stmt.h"
#include "Environment.h"
#include <memory>
#include <vector>
#include <iostream>

class Interpreter : public ExprVisitor, public StmtVisitor {
public:
    Interpreter();

    void interpret(const std::vector<std::unique_ptr<Stmt>>& statements);

    // ExprVisitor
    double visitLiteral(Literal* expr) override;
    double visitBinary(Binary* expr) override;
    double visitGrouping(Grouping* expr) override;
    double visitVariable(Variable* expr) override;

    // StmtVisitor
    void visitPrintStmt(PrintStmt* stmt) override;
    void visitExprStmt(ExprStmt* stmt) override;
    void visitVarDecl(VarDecl* stmt) override;

private:
    Environment globals;
};
