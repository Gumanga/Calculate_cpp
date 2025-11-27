#include "Calculator.h"
#include "Tokenizer.h"
#include "RPNConverter.h"
#include "Evaluator.h"
#include <stdexcept>

double Calculator::calculate(const std::string& expression) {
    Tokenizer tokenizer;
    RPNConverter converter;
    Evaluator evaluator;
    
    auto tokens = tokenizer.parseExpression(expression);
    auto rpn = converter.toRPN(tokens);
    return evaluator.evaluateRPN(rpn);
}