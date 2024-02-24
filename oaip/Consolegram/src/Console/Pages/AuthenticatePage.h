#pragma once
#include "Users/User.h"
#include "Users/UserRepository.h"

namespace Consolegram::Console::Pages::Authenticate
{
    Domain::Users::User* Show(Domain::Users::UserRepository& userRepository);
}
