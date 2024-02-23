#pragma once
#include "../Domain/Users/UserRepository.h"
#include "../SharedKernel/Result.h"

namespace Consolegram::Application::AuthenticationService
{
    Result<Domain::Users::User*> Authenticate(Domain::Users::UserRepository& usersRepository);
}
