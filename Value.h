#pragma once
#include <string>

enum class ValueType { INT, DOUBLE, STRING };

class Value {
public:
    ValueType type;
    int intValue;
    double doubleValue;
    std::string stringValue;

    // Default constructor
    Value() : type(ValueType::INT), intValue(0) {}
    
    Value(int v) { type = ValueType::INT; intValue = v; }
    Value(double v) { type = ValueType::DOUBLE; doubleValue = v; }
    Value(const std::string& v) { type = ValueType::STRING; stringValue = v; }

    double toDouble() const {
        if (type == ValueType::INT) return static_cast<double>(intValue);
        if (type == ValueType::DOUBLE) return doubleValue;
        return 0.0;
    }

    int toInt() const {
        if (type == ValueType::INT) return intValue;
        if (type == ValueType::DOUBLE) return static_cast<int>(doubleValue);
        return 0;
    }

    std::string toString() const {
        if (type == ValueType::INT) return std::to_string(intValue);
        if (type == ValueType::DOUBLE) return std::to_string(doubleValue);
        return stringValue;
    }
};