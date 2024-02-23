#include "AuthenticatePage.h"

#include <iostream>

#include "AuthenticationService.h"
#include "Users/User.h"
#include "Users/UserRepository.h"

namespace Consolegram::Console::Pages::Authenticate
{
    Domain::Users::User* Show(Domain::Users::UserRepository& usersRepository)
    {
        std::cout << "Please, login.\n";

        while (true)
        {
            Result authenticationResult{
                Application::AuthenticationService::Authenticate(usersRepository)
            };

            if (authenticationResult.IsFailure())
            {
                std::cout << authenticationResult.GetError() << '\n';
                continue;
            }

            return authenticationResult.GetValue();
        }
    }
}
