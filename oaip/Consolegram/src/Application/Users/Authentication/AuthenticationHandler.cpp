#include "AuthenticationHandler.h"
#include "../../../SharedKernel/Common.h"
#include "../../../SharedKernel/ResultT.h"

namespace Consolegram::Application::Users::AuthenticationHandler
{
    SharedKernel::ResultT<Domain::Users::User*> Handle(Domain::Users::UserRepository& usersRepository)
    {
        const std::string userName{SharedKernel::Common::GetString("Enter username:")};

        if (userName[0] == SharedKernel::Common::ExitKey)
        {
            return SharedKernel::ResultT<Domain::Users::User*>::Success(nullptr);
        }

        const auto user{usersRepository.GetByUserName(userName)};

        if (user == usersRepository.End())
        {
            return SharedKernel::ResultT<Domain::Users::User*>::Failure("User with such username was not found");
        }

        const std::string password{SharedKernel::Common::GetString("Enter password:")};

        if (password[0] == SharedKernel::Common::ExitKey)
        {
            return SharedKernel::ResultT<Domain::Users::User*>::Success(nullptr);
        }

        if (user->GetPassword() != password)
        {
            return SharedKernel::ResultT<Domain::Users::User*>::Failure("Password is incorrect");
        }

        return SharedKernel::ResultT<Domain::Users::User*>::Success(user._Ptr);
    }
}