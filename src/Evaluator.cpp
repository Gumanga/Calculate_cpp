#include "Evaluator.h"
#include <cmath>
#include <stdexcept>
#include <stack>
#include <map>
#include <functional>
#include <regex>
#include <vector>
#include <string>

const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;

double memory = 0.0;

double Evaluator::evaluateRPN(const std::vector<std::string>& rpn) {
    std::stack<double> stack;
    
    std::map<std::string, std::function<double(double)>> functions = {
      
        {"sin", [](double x) { return std::sin(x); }},
        {"cos", [](double x) { return std::cos(x); }},
        {"tan", [](double x) { return std::tan(x); }},
        {"tg", [](double x) { return std::tan(x); }},
        {"ctg", [](double x) { 
            double tan_val = std::tan(x);
            if (tan_val == 0) throw std::runtime_error("Cotangent of zero angle");
            return 1.0 / tan_val; 
        }},
        {"sqrt", [](double x) { 
            if (x < 0) throw std::runtime_error("Square root of negative number");
            return std::sqrt(x); 
        }},
        {"exp", [](double x) { return std::exp(x); }},
        {"log", [](double x) { 
            if (x <= 0) throw std::runtime_error("Logarithm of non-positive number");
            return std::log10(x); 
        }},
        {"ln", [](double x) { 
            if (x <= 0) throw std::runtime_error("Logarithm of non-positive number");
            return std::log(x); 
        }},
        {"lg", [](double x) { 
            if (x <= 0) throw std::runtime_error("Logarithm of non-positive number");
            return std::log10(x); 
        }},
        {"abs", [](double x) { return std::abs(x); }},
        {"fact", [](double x) { 
            if (x < 0 || x != static_cast<int>(x)) 
                throw std::runtime_error("Invalid factorial");
            double result = 1;
            for (int i = 2; i <= static_cast<int>(x); ++i) 
                result *= i;
            return result;
        }},
        
        {"asin", [](double x) { 
            if (x < -1 || x > 1) throw std::runtime_error("asin domain error");
            return std::asin(x); 
        }},
        {"acos", [](double x) { 
            if (x < -1 || x > 1) throw std::runtime_error("acos domain error");
            return std::acos(x); 
        }},
        {"atan", [](double x) { return std::atan(x); }},
    
        {"round", [](double x) { return std::round(x); }},
        {"floor", [](double x) { return std::floor(x); }},
        {"ceil", [](double x) { return std::ceil(x); }}
    };
    
    std::map<std::string, std::function<double(double, double)>> operators = {
        {"+", [](double a, double b) { return a + b; }},
        {"-", [](double a, double b) { return a - b; }},
        {"*", [](double a, double b) { return a * b; }},
        {"/", [](double a, double b) { 
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b; 
        }},
        {"^", [](double a, double b) { return std::pow(a, b); }},
    };
    
    // Функции для работы с памятью
    std::map<std::string, std::function<double()>> memoryFunctions = {
        {"MR", []() { return memory; }},
        {"MC", []() { memory = 0.0; return memory; }}
    };
    
    for (const auto& token : rpn) {
        if (std::regex_match(token, std::regex(R"(-?\d+(?:\.\d+)?)"))) {
            stack.push(std::stod(token));
        } else if (token == "pi") {
            stack.push(PI);
        } else if (token == "e") {
            stack.push(E);
        } else if (functions.find(token) != functions.end()) {
            if (stack.empty()) throw std::runtime_error("Not enough arguments for function: " + token);
            double arg = stack.top(); 
            stack.pop();
            stack.push(functions[token](arg));
        } else if (operators.find(token) != operators.end()) {
            if (stack.size() < 2) throw std::runtime_error("Not enough operands for operator: " + token);
            double b = stack.top(); 
            stack.pop();
            double a = stack.top(); 
            stack.pop();
            stack.push(operators[token](a, b));
        } else if (memoryFunctions.find(token) != memoryFunctions.end()) {
            stack.push(memoryFunctions[token]());
        } else if (token == "M+") {
            if (stack.empty()) throw std::runtime_error("Stack empty for M+");
            memory += stack.top();
            stack.pop();
            stack.push(memory);
        } else if (token == "M-") {
            if (stack.empty()) throw std::runtime_error("Stack empty for M-");
            memory -= stack.top();
            stack.pop();
            stack.push(memory);
        } else {
            throw std::runtime_error("Unknown token: " + token);
        }
    }
    
    if (stack.size() != 1) 
        throw std::runtime_error("Invalid expression - stack has " + std::to_string(stack.size()) + " elements");
    
    return stack.top();
}