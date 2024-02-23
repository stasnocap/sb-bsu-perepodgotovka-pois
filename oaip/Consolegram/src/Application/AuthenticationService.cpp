#include <iostream>

#include "AuthenticationService.h"
#include "../SharedKernel/Common.h"

namespace Consolegram::Application::AuthenticationService
{
    Domain::Users::User* Authenticate(Domain::Users::UserRepository& usersRepository)
    {
        std::cout << "Please, login.\n";
        
        while (true)
        {
            const std::string userName{SharedKernel::Common::GetString("Enter username:")};

            if (userName[0] == SharedKernel::Common::ExitKey)
            {
                return nullptr;
            }

            const auto user{usersRepository.GetByUserName(userName)};

            if (user == usersRepository.End())
            {
                std::cout << "User with such username was not found\n";
                continue;
            }

            const std::string password{SharedKernel::Common::GetString("Enter password:")};

            if (password[0] == SharedKernel::Common::ExitKey)
            {
                return nullptr;
            }

            if (user->GetPassword() != password)
            {
                std::cout << "Password is incorrect\n";
                continue;
            }

            return user._Ptr;
        }
    }
}
