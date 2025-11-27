#pragma once
#include <string>
#include <vector>
#include <regex>

class Tokenizer {
private:
    std::regex pattern; 
    
public:
    Tokenizer();
    std::vector<std::string> parseExpression(const std::string& expr);
};