#pragma once
#include <map>
#include <string>

namespace Consolegram::SharedKernel
{
    class Config
    {
        std::map<std::string, std::string> _settings{};
        bool _isDevelopment{};
        bool _isProduction{};

        void ReadSettings(std::string_view appsettingsFileName, bool isRequired);

        std::string GetEnvironment(int argc, char* argv[]);

    public:
        std::string operator[](const std::string& key) const;

        [[nodiscard]] bool IsDevelopment() const;

        [[nodiscard]] bool IsProduction() const;

        void Init(int argc, char* argv[]);
    };
}
