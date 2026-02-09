#pragma once
#include "Value.h"
#include <unordered_map>
#include <string>
#include <stdexcept>

class Environment {
public:
    void define(const std::string& name, Value value) {
        values[name] = value;
    }

    Value get(const std::string& name) {
        if (values.find(name) != values.end())
            return values[name];
        throw std::runtime_error("Undefined variable: " + name);
    }

private:
    std::unordered_map<std::string, Value> values;
};
