#pragma once
#include <string>
#include <iostream>

enum class ValueType { INT, DOUBLE, STRING };

class Value {
public:
    ValueType type;
    int intValue;
    double doubleValue;
    std::string stringValue;

    // Constructors
    Value(int v) { type = ValueType::INT; intValue = v; }
    Value(double v) { type = ValueType::DOUBLE; doubleValue = v; }
    Value(const std::string& v) { type = ValueType::STRING; stringValue = v; }

    void print() {
        switch(type) {
            case ValueType::INT:    std::cout << intValue; break;
            case ValueType::DOUBLE: std::cout << doubleValue; break;
            case ValueType::STRING: std::cout << stringValue; break;
        }
    }

    double asNumber() {
        if (type == ValueType::INT) return intValue;
        if (type == ValueType::DOUBLE) return doubleValue;
        throw std::runtime_error("Cannot use string in numeric expression");
    }
};
