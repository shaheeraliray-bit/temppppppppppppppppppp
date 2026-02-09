#include "Parser.h"

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        statements.push_back(statement());
    }
    return statements;
}

std::unique_ptr<Stmt> Parser::statement() {
    if (match({TokenType::VAR})) {
        return varDeclaration();
    }
    if (match({TokenType::LOGONCONSOLE})) {
        return printStatement();
    }
    return expressionStatement();
}

std::unique_ptr<Stmt> Parser::varDeclaration() {
    Token name = advance();
    
    std::unique_ptr<Expr> initializer = nullptr;
    if (match({TokenType::EQUAL})) {
        initializer = expression();
    }
    
    return std::make_unique<VarDecl>(name.lexeme, std::move(initializer));
}

std::unique_ptr<Stmt> Parser::printStatement() {
    auto value = expression();
    return std::make_unique<PrintStmt>(std::move(value));
}

std::unique_ptr<Stmt> Parser::expressionStatement() {
    auto expr = expression();
    return std::make_unique<ExprStmt>(std::move(expr));
}

std::unique_ptr<Expr> Parser::expression() {
    return assignment();
}

std::unique_ptr<Expr> Parser::assignment() {
    auto expr = logicalOr();

    if (match({TokenType::EQUAL})) {
        Token equals = previous();
        auto value = assignment();
        
        if (Variable* var = dynamic_cast<Variable*>(expr.get())) {
            return expr;
        }
    }

    return expr;
}

std::unique_ptr<Expr> Parser::logicalOr() {
    auto expr = logicalAnd();
    return expr;
}

std::unique_ptr<Expr> Parser::logicalAnd() {
    auto expr = equality();
    return expr;
}

std::unique_ptr<Expr> Parser::equality() {
    auto expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token op = previous();
        auto right = comparison();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::comparison() {
    auto expr = addition();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        Token op = previous();
        auto right = addition();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::addition() {
    auto expr = multiplication();

    while (match({TokenType::MINUS, TokenType::PLUS})) {
        Token op = previous();
        auto right = multiplication();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::multiplication() {
    auto expr = unary();

    while (match({TokenType::SLASH, TokenType::STAR, TokenType::PERCENT})) {
        Token op = previous();
        auto right = unary();
        expr = std::make_unique<Binary>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::unary() {
    if (match({TokenType::BANG_EQUAL, TokenType::MINUS})) {
        Token op = previous();
        auto right = unary();
        return std::make_unique<Unary>(op, std::move(right));
    }

    return primary();
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({TokenType::NUMBER})) {
        return std::make_unique<Literal>(Value(std::stod(previous().lexeme)));
    }

    if (match({TokenType::STRING_LIT})) {
        return std::make_unique<Literal>(Value(previous().lexeme));
    }

    if (match({TokenType::IDENTIFIER})) {
        return std::make_unique<Variable>(previous().lexeme);
    }

    if (match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        advance(); // consume ')'
        return std::make_unique<Grouping>(std::move(expr));
    }

    return std::make_unique<Literal>(Value(0));
}

Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const {
    return tokens[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}