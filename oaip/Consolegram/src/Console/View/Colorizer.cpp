#include "Colorizer.h"

#include <string_view>
#include <windows.h>

namespace Consolegram::Console::View::Colorizer
{
    const HANDLE HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    std::string_view SetColor(const WORD wAttributes)
    {
        SetConsoleTextAttribute(HConsole, wAttributes);
        return "";
    }

    std::string_view SetBlueColor()
    {
        return SetColor(1);
    }

    std::string_view SetWhiteColor()
    {
        return SetColor(7);
    }

    std::string_view SetDarkYellowColor()
    {
        return SetColor(6);
    }

    std::string_view SetGrayColor()
    {
        return SetColor(8);
    }

    std::string_view SetPurpleColor()
    {
        return SetColor(5);
    }
}
