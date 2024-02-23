#pragma once
#include "../../../Domain/Users/UserRepository.h"
#include "../../../SharedKernel/Result.h"

namespace Consolegram::Application::Users::AuthenticationHandler
{
    Result<Domain::Users::User*> Handle(Domain::Users::UserRepository& usersRepository);
}
