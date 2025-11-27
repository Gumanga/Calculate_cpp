#pragma once
#include <string>
#include <vector>

class RPNConverter {
public:
    std::vector<std::string> toRPN(const std::vector<std::string>& tokens);
};