#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace Consolegram::Console
{
    constexpr inline char ExitKey{'\n'};

    constexpr inline int ExitCode{-1};

    std::string GetString(std::string_view ask);

    std::string GetString(std::string_view ask, const std::function<bool(std::string_view)>& condition);

    int GetInt(std::string_view ask);

    int GetInt(std::string_view ask, const std::function<bool(int)>& condition);
}