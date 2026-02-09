#include "Interpreter.h"
#include <iostream>
#include <cmath>

void Interpreter::interpret(std::vector<std::unique_ptr<Stmt>>& statements) {
    for (auto& stmt : statements) {
        stmt->accept(this);
    }
}

Value Interpreter::visitLiteral(Literal* expr) {
    return expr->value;
}

Value Interpreter::visitVariable(Variable* expr) {
    return env.get(expr->name);
}

Value Interpreter::visitUnary(Unary* expr) {
    Value right = expr->right->accept(this);

    switch (expr->op.type) {
        case TokenType::MINUS:
            return Value(-right.toDouble());
        case TokenType::BANG_EQUAL:
            return Value(right.toInt() == 0 ? 1 : 0);
        default:
            return Value(0);
    }
}

Value Interpreter::visitBinary(Binary* expr) {
    Value left = expr->left->accept(this);
    Value right = expr->right->accept(this);

    switch (expr->op.type) {
        case TokenType::PLUS:
            return Value(left.toDouble() + right.toDouble());
        case TokenType::MINUS:
            return Value(left.toDouble() - right.toDouble());
        case TokenType::STAR:
            return Value(left.toDouble() * right.toDouble());
        case TokenType::SLASH:
            if (right.toDouble() != 0)
                return Value(left.toDouble() / right.toDouble());
            return Value(0);
        case TokenType::PERCENT:
            return Value(static_cast<int>(left.toDouble()) % static_cast<int>(right.toDouble()));
        case TokenType::GREATER:
            return Value(left.toDouble() > right.toDouble() ? 1 : 0);
        case TokenType::GREATER_EQUAL:
            return Value(left.toDouble() >= right.toDouble() ? 1 : 0);
        case TokenType::LESS:
            return Value(left.toDouble() < right.toDouble() ? 1 : 0);
        case TokenType::LESS_EQUAL:
            return Value(left.toDouble() <= right.toDouble() ? 1 : 0);
        case TokenType::EQUAL_EQUAL:
            return Value(left.toDouble() == right.toDouble() ? 1 : 0);
        case TokenType::BANG_EQUAL:
            return Value(left.toDouble() != right.toDouble() ? 1 : 0);
        default:
            return Value(0);
    }
}

Value Interpreter::visitGrouping(Grouping* expr) {
    return expr->expression->accept(this);
}

void Interpreter::visitVarDecl(VarDecl* stmt) {
    Value value;
    if (stmt->initializer != nullptr) {
        value = stmt->initializer->accept(this);
    }
    env.define(stmt->name, value);
}

void Interpreter::visitExprStmt(ExprStmt* stmt) {
    stmt->expression->accept(this);
}

void Interpreter::visitPrintStmt(PrintStmt* stmt) {
    Value value = stmt->expression->accept(this);
    std::cout << value.toString() << std::endl;
}