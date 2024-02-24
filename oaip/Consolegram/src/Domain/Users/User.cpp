#include "User.h"

#include <format>

namespace Consolegram::Domain::Users
{
    User::User(const long id, std::string userName, std::string password)
        : Entity(id), _name{std::move(userName)}, _password{std::move(password)}
    {
    }

    std::string_view User::GetName() const
    {
        return _name;
    }

    std::string_view User::GetPassword() const
    {
        return _password;
    }
}
