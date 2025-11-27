#include <iostream>
#include <string>
#include "Calculator.h"

int main() {
    Calculator calc;
    std::string input;
    
    std::cout << "Enter 'exit' to quit" << std::endl;
    std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
    std::cout << "|  BASIC MATH       |  TRIGONOMETRY     |  FUNCTIONS        |" << std::endl;
    std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
    std::cout << "|      + - * /      |  sin() cos()      |  sqrt()           |" << std::endl;
    std::cout << "|      ^            |  tan() ctg()      |  exp() log()      |" << std::endl;
    std::cout << "|      ()           |  asin() acos()    |  ln() lg()        |" << std::endl;
    std::cout << "|  M+ M- MR MC      |  atan()           |  abs() fact()     |" << std::endl;
    std::cout << "|                   |                   |  round() floor()  |" << std::endl;
    std::cout << "|                   |                   |  ceil()           |" << std::endl;
    std::cout << "+-------------------+-------------------+-------------------+" << std::endl;
    std::cout << std::endl;
    std::cout << "CONSTANTS: pi  e" << std::endl;
    std::cout << "MEMORY: M+ (add to memory), M- (subtract), MR (recall), MC (clear)" << std::endl;
    std::cout << std::endl;

    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "exit" || input == "quit") break;
        if (input.empty()) continue;
        
        try {
            double result = calc.calculate(input);
            std::cout << "= " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}