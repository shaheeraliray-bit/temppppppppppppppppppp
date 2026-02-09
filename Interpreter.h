#pragma once
#include <vector>
#include <memory>
#include "Expr.h"
#include "Stmt.h"
#include "Environment.h"

class Interpreter : public ExprVisitor, public StmtVisitor {
private:
    Environment env;

public:
    Interpreter() {}

    // ExprVisitor methods
    Value visitLiteral(Literal* expr) override;
    Value visitVariable(Variable* expr) override;
    Value visitUnary(Unary* expr) override;
    Value visitBinary(Binary* expr) override;
    Value visitGrouping(Grouping* expr) override;

    // StmtVisitor methods
    void visitVarDecl(VarDecl* stmt) override;
    void visitExprStmt(ExprStmt* stmt) override;
    void visitPrintStmt(PrintStmt* stmt) override;

    void interpret(std::vector<std::unique_ptr<Stmt>>& statements);
};