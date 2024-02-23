#pragma once
#include "../../../Domain/Users/UserRepository.h"
#include "../../../SharedKernel/ResultT.h"

namespace Consolegram::Application::Users::AuthenticationHandler
{
    SharedKernel::ResultT<Domain::Users::User*> Handle(Domain::Users::UserRepository& usersRepository);
}
