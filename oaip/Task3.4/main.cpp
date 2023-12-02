#include <iostream>
#include <algorithm>

void printResult(const double &number1,
                 const double &number2,
                 const char &operation,
                 const double &result) {
    std::cout << number1 << ' ' << operation << ' ' << number2 << " = " << result;
}

double calculate(const double &number1,
                 const double &number2,
                 const char &operation) {
    double result{};

    switch (operation) {
        case '+':
            result = number1 + number2;
            break;
        case '-':
            result = number1 - number2;
            break;
        case '*':
            result = number1 * number2;
            break;
        case '/':
            result = number1 / number2;
            break;
        default:
            throw std::invalid_argument("Unknown operation");
    }

    return result;
}

char getOperation() {
    std::cout << "Enter operation (+, -, *, /):";

    char operation{};
    std::cin >> operation;

    return operation;
}

double getNumber() {
    std::cout << "Enter number:";

    int num{};
    std::cin >> num;

    return num;
}

int main() {
    const double number1{getNumber()};

    const char operation{getOperation()};

    const double number2{getNumber()};

    const double result{calculate(number1, number2, operation)};

    printResult(number1, number2, operation, result);

    return EXIT_SUCCESS;
}