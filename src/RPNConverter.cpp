#include "RPNConverter.h"
#include <stack>
#include <map>
#include <regex>
#include <stdexcept>
#include <algorithm>

std::vector<std::string> RPNConverter::toRPN(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> stack;
    
    std::map<std::string, int> priority = {
        {"^", 4}, {"*", 3}, {"/", 3}, {"+", 2}, {"-", 2}
    };
    
    auto isOperator = [](const std::string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
    };
    
    auto isFunction = [](const std::string& token) {
        static const std::vector<std::string> functions = {
            "sin", "cos", "tan", "tg", "ctg", "sqrt", "exp", "log", "ln", "lg", 
            "abs", "fact", "asin", "acos", "atan", "round", "floor", "ceil", "MR", "MC"
        };
        return std::find(functions.begin(), functions.end(), token) != functions.end();
    };
    
    for (const auto& token : tokens) {
        if (std::regex_match(token, std::regex(R"(-?\d+(?:\.\d+)?)")) || token == "pi" || token == "e") {
            output.push_back(token);
        } else if (isFunction(token)) {
            stack.push(token);
        } else if (isOperator(token)) {
            while (!stack.empty() && isOperator(stack.top()) && 
                   priority[stack.top()] >= priority[token]) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
        } else if (token == "(") {
            stack.push(token);
        } else if (token == ")") {
            while (!stack.empty() && stack.top() != "(") {
                output.push_back(stack.top());
                stack.pop();
            }
            if (stack.empty()) throw std::runtime_error("Unclosed parenthesis");
            stack.pop();
            if (!stack.empty() && isFunction(stack.top())) {
                output.push_back(stack.top());
                stack.pop();
            }
        } else if (token == "M+" || token == "M-") {
          
            output.push_back(token);
        }
    }
    
    while (!stack.empty()) {
        if (stack.top() == "(") throw std::runtime_error("Unclosed parenthesis");
        output.push_back(stack.top());
        stack.pop();
    }
    
    return output;
}