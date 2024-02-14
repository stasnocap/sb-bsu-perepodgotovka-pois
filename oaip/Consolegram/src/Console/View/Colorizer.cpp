#include "Colorizer.h"

#include <string_view>
#include <windows.h>

namespace Consolegram::Console::View::Colorizer
{
    std::string_view SetColor(const HANDLE hConsole, const WORD wAttributes)
    {
        SetConsoleTextAttribute(hConsole, wAttributes);
        return "";
    }

    std::string_view SetBlueColor(const HANDLE hConsole)
    {
        return SetColor(hConsole, 1);
    }

    std::string_view SetBlackColor(const HANDLE hConsole)
    {
        return SetColor(hConsole, 0);
    }

    std::string_view SetDarkYellowColor(const HANDLE hConsole)
    {
        return SetColor(hConsole, 6);
    }

    std::string_view SetGrayColor(const HANDLE hConsole)
    {
        return SetColor(hConsole, 8);
    }

    std::string_view SetPurpleColor(const HANDLE hConsole)
    {
        return SetColor(hConsole, 5);
    }
}
