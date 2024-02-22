#include "Formatter.h"

#include "Colorizer.h"

namespace Consolegram::Console::View::Formatter
{
    std::string FormatMessageText(const std::string_view text)
    {
        std::string result{text};
        if (text.length() < Colorizer::ChatSeparator.size())
        {
            return result;
        }

        for (size_t i = 0; i < text.length() / Colorizer::ChatSeparator.size(); ++i)
        {
            result.insert((i + 1) * Colorizer::ChatSeparator.size() - 1, "\n");
        }

        return result;
    }
}
