#include "Tokenizer.h"
#include <regex>
#include <algorithm>

Tokenizer::Tokenizer() : pattern(R"((?:sin|cos|tan|tg|ctg|sqrt|exp|log|ln|lg|abs|fact|asin|acos|atan|round|floor|ceil|pi|e|M\+|M\-|MR|MC|\d+(?:\.\d+)?|[+\-*/^()]))") {}

std::vector<std::string> Tokenizer::parseExpression(const std::string& expr) {
    std::string processed = expr;
    
    processed.erase(std::remove(processed.begin(), processed.end(), ' '), processed.end());
    
    if (!processed.empty() && processed[0] == '-') 
        processed = "0" + processed;
    
    size_t pos = 0;
    while ((pos = processed.find("(-", pos)) != std::string::npos) {
        processed.replace(pos, 2, "(0-");
        pos += 3;
    }
    
    // Токенизация
    std::vector<std::string> tokens;
    std::sregex_iterator it(processed.begin(), processed.end(), pattern);
    std::sregex_iterator end;
    
    while (it != end) {
        tokens.push_back(it->str());
        ++it;
    }
    
    return tokens;
}