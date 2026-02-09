#include "Interpreter.h"
#include <stdexcept>

// ---------------- CONSTRUCTOR ----------------
Interpreter::Interpreter() {}

// ---------------- INTERPRET ----------------
void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>>& statements) {
    for (const auto& stmt : statements) {
        stmt->accept(this);
    }
}

// ---------------- EXPR VISITORS ----------------
Value Interpreter::visitLiteral(Literal* expr) {
    std::string lex = expr->value.lexeme;
    if (lex.find('.') != std::string::npos)
        return Value(std::stod(lex));
    return Value(std::stoi(lex));
}

double Interpreter::visitGrouping(Grouping* expr) {
    return expr->expression->accept(this);
}

double Interpreter::visitBinary(Binary* expr) {
    double left = expr->left->accept(this);
    double right = expr->right->accept(this);

    switch (expr->op.type) {
        case TokenType::PLUS:  return left + right;
        case TokenType::MINUS: return left - right;
        case TokenType::STAR:  return left * right;
        case TokenType::SLASH: return left / right;
        default:
            throw std::runtime_error("Unknown binary operator");
    }
}

double Interpreter::visitVariable(Variable* expr) {
    Value val = globals.get(expr->name);
    if (std::holds_alternative<int>(val)) return std::get<int>(val);
    if (std::holds_alternative<double>(val)) return std::get<double>(val);
    throw std::runtime_error("Cannot use string in numeric expression");
}

// ---------------- STMT VISITORS ----------------
void Interpreter::visitPrintStmt(PrintStmt* stmt) {
    double value = stmt->expression->accept(this);
    std::cout << value << "\n";
}

void Interpreter::visitExprStmt(ExprStmt* stmt) {
    stmt->expression->accept(this);
}

void Interpreter::visitVarDecl(VarDecl* stmt) {
    double value = stmt->initializer->accept(this);
    globals.define(stmt->name, value);
}
