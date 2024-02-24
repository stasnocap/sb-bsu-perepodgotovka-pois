#include "GetUserByNameHandler.h"

namespace Consolegram::Application::Users::GetUserByName
{
    SharedKernel::ResultT<Domain::Users::User*> Handle(const std::string_view name, Domain::Users::UserRepository& userRepository)
    {
        const auto user{userRepository.GetByUserName(name)};

        if (user == userRepository.End())
        {
            return SharedKernel::ResultT<Domain::Users::User*>::Failure("User with such username was not found");
        }
        
        return SharedKernel::ResultT<Domain::Users::User*>::Success(user._Ptr);
    }
}