#include "AuthenticatePage.h"

#include <iostream>

#include "Users/User.h"
#include "Users/UserRepository.h"
#include "Users/Authentication/AuthenticationHandler.h"

namespace Consolegram::Console::Pages::Authenticate
{
    Domain::Users::User* Show(Domain::Users::UserRepository& usersRepository)
    {
        std::cout << "Please, login.\n";

        while (true)
        {
            SharedKernel::ResultT authenticationResult{
                Application::Users::AuthenticationHandler::Handle(usersRepository)
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