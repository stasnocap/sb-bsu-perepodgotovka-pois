#include "Common.h"
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
}