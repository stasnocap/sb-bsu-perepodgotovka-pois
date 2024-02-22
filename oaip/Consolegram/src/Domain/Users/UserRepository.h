#pragma once
#include <vector>
#include "User.h"
#include "../Messages/Message.h"
#include "../../SharedKernel/Repository.h"
#include "../../SharedKernel/Config.h"

namespace Consolegram::Domain::Users
{
    class UserRepository : public SharedKernel::Repository<User>
    {
    public:
        explicit UserRepository(const SharedKernel::Config& config);

        std::vector<User>::iterator GetByUserName(std::string_view userName);

        std::vector<User> GetUsersByMessages(const std::vector<Messages::Message>& messages);
    };
}
