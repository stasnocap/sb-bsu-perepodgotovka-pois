#include "Common.h"

#include <cassert>
#include <iostream>
#include <string>

namespace Consolegram::SharedKernel
{
    std::string GetString(const std::string_view ask)
    {
        std::cout << ask;
        std::string input{};
        std::getline(std::cin >> std::ws, input);
        return input;
    }

    int GetInt(const std::string_view message) {
        while (true) {
            const std::string input{GetString(message)};

            try {
                return std::stoi(input);
            } catch ([[maybe_unused]] std::exception &exception) {
                std::cout << "Can't parse to int: " << input << "\r\n";
            }
        }
    }

    int GetInt(const std::string_view message, const std::function<bool(int)>& condition) {
        assert(condition && "Condition is null");

        int result;
        do {
            result = GetInt(message);
        } while (!condition(result));

        return result;
    }
}