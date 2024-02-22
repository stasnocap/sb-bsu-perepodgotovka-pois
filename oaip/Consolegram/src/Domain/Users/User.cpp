#include "User.h"

#include <format>
#include <sstream>

namespace Consolegram::Domain::Users
{
    User::User(const long id, std::string userName, std::string password)
        : SharedKernel::Entity(id), _name{std::move(userName)}, _password{std::move(password)}
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

    std::string User::ToFileString() const
    {
        std::ostringstream oStringStream{};
        
        oStringStream
            << GetId() << '\t'
            << GetName() << '\t'
            << GetPassword();
        
        return oStringStream.str();
    }
}
