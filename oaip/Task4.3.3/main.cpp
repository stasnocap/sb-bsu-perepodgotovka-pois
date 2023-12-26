#include <iostream>
#include <array>
#include <algorithm>
#include <cassert>
#include <sstream>

namespace input {
    typedef bool (*condition_t)(double number);

    std::string getString(std::string_view message);

    double getDouble(std::string_view message);

    double getDouble(std::string_view message, input::condition_t condition);
}

struct Condition {
    int downLimit{};
    int upLimit{};
    std::string_view message{};
    input::condition_t value{};
};

int main() {
    constexpr Condition positiveCondition{1, 5, "positive", [](double number) -> bool { return number > 0; }};
    constexpr Condition negativeCondition{6, 10, "negative", [](double number) -> bool { return number < 0; }};
    constexpr Condition fromTenToHundredCondition{11, 15, "10 < x < 100",
                                                  [](double number) -> bool { return number > 10 && number < 100; }};
    constexpr Condition evenCondition{16, 20, "even",
                                      [](double number) -> bool { return static_cast<int>(number) % 2 == 0; }};
    constexpr Condition moreThanHundredCondition{21, 25, "x > 100", [](double number) -> bool { return number > 100; }};

    std::array<Condition, 5> conditions{
            positiveCondition,
            negativeCondition,
            fromTenToHundredCondition,
            evenCondition,
            moreThanHundredCondition,
    };

    for (int i = 1; i <= moreThanHundredCondition.upLimit; ++i) {
        Condition *conditionPtr = std::find_if(conditions.begin(), conditions.end(), [i](const Condition &condition) {
            return i >= condition.downLimit && i <= condition.upLimit;
        });

        std::stringstream message{};
        message << "\r\nEnter number " << i << " (" << conditionPtr->message << "):";

        input::getDouble(message.str(), conditionPtr->value);
    }

    return EXIT_SUCCESS;
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
            } catch (std::exception &exception) {
                std::cout << "Can't parse to number: " << input << "\r\n";
            }
        }
    }

    double getDouble(std::string_view message, input::condition_t condition) {
        assert(condition && "Condition is null");

        double result{};
        do {
            result = getDouble(message);
        } while (!condition(result));

        return result;
    }
}