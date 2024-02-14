#include <iostream>

#include "AuthenticationService.h"
#include "../SharedKernel/Common.h"

namespace Consolegram::Application::AuthenticationService
{
    Domain::Users::User* Authenticate(Domain::Users::UserRepository& usersRepository)
    {
        while (true)
        {
            const std::string userName{SharedKernel::GetString("Please, login.\nEnter username:")};

            const auto user{usersRepository.GetByUserName(userName)};

            if (user == usersRepository.End())
            {
                std::cout << "User with such username was not found\n";
                continue;
            }

            const std::string password{SharedKernel::GetString("Enter password:")};

            if (user->GetPassword() != password)
            {
                std::cout << "Password is incorrect\n";
                continue;
            }

            return user._Ptr;
        }
    }
}
