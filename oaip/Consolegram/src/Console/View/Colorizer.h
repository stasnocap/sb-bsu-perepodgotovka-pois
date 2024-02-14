#pragma once
#include <string_view>
#include <windows.h>

namespace Consolegram::Console::View::Colorizer
{
    std::string_view SetColor(HANDLE hConsole, WORD wAttributes);

    std::string_view SetBlueColor(HANDLE hConsole);

    std::string_view SetBlackColor(HANDLE hConsole);

    std::string_view SetDarkYellowColor(HANDLE hConsole);

    std::string_view SetGrayColor(HANDLE hConsole);

    std::string_view SetPurpleColor(HANDLE hConsole);
}
