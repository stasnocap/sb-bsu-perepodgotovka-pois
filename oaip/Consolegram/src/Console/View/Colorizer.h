#pragma once
#include <string_view>
#include <windows.h>

namespace Consolegram::Console::View::Colorizer
{
    constexpr inline std::string_view ChatSeparator{"------------------------------------\n"};
    
    std::string_view SetColor(WORD wAttributes);

    std::string_view SetBlueColor();

    std::string_view SetBlackColor();

    std::string_view SetDarkYellowColor();

    std::string_view SetGrayColor();

    std::string_view SetPurpleColor();
}
