#include <format>
#include <fstream>
#include <map>
#include <sstream>
#include "../SharedKernel/Common.h"
#include "../SharedKernel/Config.h"

namespace Consolegram::SharedKernel
{
    constexpr std::string_view EnvironmentKey{"--environment"};
    constexpr std::string_view DevelopmentEnvironment{"development"};
    constexpr std::string_view ProductionEnvironment{"production"};
    constexpr std::string_view AppsettingsFileNameWithoutExtension{"appsettings"};

    void Config::ReadSettings(std::string_view appsettingsFileName, bool isRequired)
    {
        std::ifstream iFileStream(appsettingsFileName.data());

        if (!iFileStream.is_open())
        {
            if (isRequired)
            {
                throw std::invalid_argument(std::format("The {} cannot be opened!", appsettingsFileName));
            }

            return;
        }

        iFileStream.get();
        iFileStream.get();
        iFileStream.get();

        std::string line{};
        while (std::getline(iFileStream, line))
        {
            std::istringstream iStringStream(line);

            std::string key{};
            if (!std::getline(iStringStream, key, '='))
            {
                break;
            }

            std::string value{};
            if (!std::getline(iStringStream, value))
            {
                break;
            }

            _settings[key] = value;
        }
    }

    std::string Config::GetEnvironment(const int argc, char* argv[])
    {
        std::string environment{};
        for (int i = 1; i < argc; ++i)
        {
            const std::string lowerArg{ToLower(argv[i])};
            if (lowerArg == EnvironmentKey && i + 1 < argc)
            {
                const std::string nextLowerArg{ToLower(argv[i + 1])};
                if (nextLowerArg == ProductionEnvironment)
                {
                    environment = ProductionEnvironment;
                    _isDevelopment = false;
                    _isProduction = true;
                    break;
                }
            }
        }

        if (environment.empty())
        {
            environment = DevelopmentEnvironment;
            _isDevelopment = true;
            _isProduction = false;
        }

        return environment;
    }

    std::string Config::operator[](const std::string& key) const
    {
        return _settings.at(key);
    }

    bool Config::IsDevelopment() const
    {
        return _isDevelopment;
    }

    bool Config::IsProduction() const
    {
        return _isProduction;
    }

    void Config::Init(const int argc, char* argv[])
    {
        std::string environment(GetEnvironment(argc, argv));
        environment[0] = static_cast<char>(std::toupper(environment[0]));
        ReadSettings(std::format("{}.txt", AppsettingsFileNameWithoutExtension), true);
        ReadSettings(std::format("{}.{}.txt", AppsettingsFileNameWithoutExtension, environment), false);
    }
}
