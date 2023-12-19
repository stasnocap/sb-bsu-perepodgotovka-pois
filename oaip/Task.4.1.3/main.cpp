#include <iostream>

namespace user {
    inline constexpr std::string_view password{"password"};
}

namespace input {
    std::string getString(std::string_view message);

    double getDouble(std::string_view message);

    char getChar(std::string_view message);
}

namespace calc {
    double add(double number1, double number2);

    double subtract(double number1, double number2);

    double multiply(double number1, double number2);

    double divide(double number1, double number2);

    typedef double (*operationPtr)(double number1, double number2);

    calc::operationPtr getOperation(char operation);

    calc::operationPtr getOperation(std::string_view message);
}

namespace app {
    void authenticate();
    
    void calculator();
}

int main() {
    app::authenticate();
    app::calculator();
    return EXIT_SUCCESS;
}

namespace app {
    void authenticate() {
        while (true) {
            const std::string password{input::getString("Please enter password: ")};

            if (password == user::password) {
                break;
            }

            std::cout << "Wrong password. Please try again\n";
        }
    }

    void calculator() {
        while (true) {
            const double number1{input::getDouble("Please enter number1: ")};

            const double number2{input::getDouble("Please enter number2: ")};

            const calc::operationPtr operation{calc::getOperation("Please enter operation(+,-,*,/): ")};

            try {
                const double result{operation(number1, number2)};
                std::cout << "Result: " << result;
                break;
            } catch (std::invalid_argument exception) {
                std::cout << exception.what();
            }
        }
    }
}

namespace calc {
    double add(double number1, double number2) {
        return number1 + number2;
    }

    double subtract(double number1, double number2) {
        return number1 - number2;
    }

    double multiply(double number1, double number2) {
        return number1 * number2;
    }

    double divide(double number1, double number2) {
        if (number2 == 0) {
            throw std::invalid_argument("Can't divide by zero");
        }

        return number1 / number2;
    }

    calc::operationPtr getOperation(char operation) {
        switch (operation) {
            case '+':
                return add;
            case '-':
                return subtract;
            case '*':
                return multiply;
            case '/':
                return divide;
            default:
                throw std::invalid_argument("Unknown operation");
        }
    }

    calc::operationPtr getOperation(std::string_view message) {
        while (true) {
            const char operationChar{input::getChar(message)};

            try {
                return calc::getOperation(operationChar);
            } catch (std::invalid_argument exception) {
                std::cout << exception.what() << "\n";
            }
        }
    }
}

namespace input {
    std::string getString(std::string_view message) {
        std::cout << message;
        std::string input{};
        std::getline(std::cin >> std::ws, input);
        return input;
    }

    double getDouble(std::string_view message) {
        while (true) {
            const std::string input{getString(message)};

            try {
                return std::stod(input);
            } catch (std::exception exception) {
                std::cout << "Can't parse to number: " << input << "\n";
            }
        }
    }

    char getChar(std::string_view message) {
        return getString(message)[0];
    }
}