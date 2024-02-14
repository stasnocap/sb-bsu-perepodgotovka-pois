#pragma once
#include <string>
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Users
{
    class User : public SharedKernel::Entity
    {
        std::string _name{};
        std::string _password{};

    public:
        explicit User(long id, std::string userName, std::string password);

        [[nodiscard]] std::string_view GetName() const;

        [[nodiscard]] std::string_view GetPassword() const;
    };
}