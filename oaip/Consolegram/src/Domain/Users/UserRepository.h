#pragma once
#include <vector>
#include "User.h"
#include "../../SharedKernel/Repository.h"
#include "../../SharedKernel/Config.h"

namespace Consolegram::Domain::Users
{
    class UserRepository : public SharedKernel::Repository<User>
    {
    public:
        explicit UserRepository(const SharedKernel::Config& config);

        std::vector<User>::iterator GetByUserName(std::string_view userName);
    };
}
