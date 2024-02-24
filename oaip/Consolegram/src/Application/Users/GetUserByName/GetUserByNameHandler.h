#pragma once
#include "../../../Domain/Users/User.h"
#include "../../../Domain/Users/UserRepository.h"
#include "../../../SharedKernel/ResultT.h"

namespace Consolegram::Application::Users::GetUserByName
{
    SharedKernel::ResultT<Domain::Users::User*> Handle(std::string_view name,
                                                       Domain::Users::UserRepository& userRepository);
}