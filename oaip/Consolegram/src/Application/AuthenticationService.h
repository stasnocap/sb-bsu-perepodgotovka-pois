#pragma once
#include "../Domain/Users/UserRepository.h"

namespace Consolegram::Application::AuthenticationService
{
    Domain::Users::User* Authenticate(Domain::Users::UserRepository& usersRepository);
}
