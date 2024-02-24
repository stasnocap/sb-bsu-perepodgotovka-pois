#include "Input.h"

#include <string_view>
#include <cassert>

namespace Consolegram::Console
{
    std::string GetString(const std::string_view ask)
    {
        std::cout << ask;
        std::string input{};
        if (std::cin.peek() == ExitKey)
        {
            std::cin.get();
            return {ExitKey};
        }
        
        std::getline(std::cin >> std::ws, input);
        return input;
    }
    
    std::string GetString(const std::string_view ask, const std::function<bool(std::string_view)>& condition)
    {
        assert(condition && "Condition is null");

        std::string result;
        do
        {
            result = GetString(ask);
        }
        while (!condition(result));

        return result;
    }

    int GetInt(const std::string_view ask)
    {
        while (true)
        {
            const std::string input{GetString(ask)};

            if (input[0] == ExitKey)
            {
                return ExitCode;
            }

            try
            {
                return std::stoi(input);
            }
            catch ([[maybe_unused]] std::exception& exception)
            {
                std::cout << "Can't parse to int: " << input << "\r\n";
            }
        }
    }

    int GetInt(const std::string_view ask, const std::function<bool(int)>& condition)
    {
        assert(condition && "Condition is null");

        int result;
        do
        {
            result = GetInt(ask);
        }
        while (!condition(result));

        return result;
    }
}
