#include "AuthenticatePage.h"

#include <iostream>

#include "../Input.h"
#include "Users/User.h"
#include "Users/UserRepository.h"
#include "Users/GetUserByName/GetUserByNameHandler.h"

namespace Consolegram::Console::Pages::Authenticate
{
    Domain::Users::User* Show(Domain::Users::UserRepository& userRepository)
    {
        std::cout << "Please, login.\n";

        while (true)
        {
            const std::string userName{GetString("Enter username:")};

            if (userName[0] == ExitKey)
            {
                return nullptr;
            }

            const SharedKernel::ResultT getByUserNameResult{
                Application::Users::GetUserByName::Handle(userName, userRepository)
            };

            if (getByUserNameResult.IsFailure())
            {
                std::cout << getByUserNameResult.GetError() << '\n';
                continue;
            }

            const std::string password{GetString("Enter password:")};

            if (password[0] == ExitKey)
            {
                return nullptr;
            }

            Domain::Users::User* user{getByUserNameResult.GetValue()};
            if (user->GetPassword() != password)
            {
                std::cout << "Password is incorrect\n";
                continue;
            }

            return user;
        }
    }
}