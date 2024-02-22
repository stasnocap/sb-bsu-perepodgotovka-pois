#include "../../Domain/Users/UserRepository.h"

#include <sstream>

namespace Consolegram::Domain::Users
{
    UserRepository::UserRepository(const SharedKernel::Config& config) : Repository{
        config["UsersFileRelativePath"],
        [](std::ifstream& fileStream)
        {
            std::vector<User> users{};

            long id{};
            std::string userName{};
            std::string password{};

            while (!fileStream.eof())
            {
                fileStream >> id;
                fileStream >> userName;
                fileStream >> password;

                users.emplace_back(id, userName,
                                   password);
            }

            return users;
        },
        [](const User& user)
        {
            std::ostringstream oStringStream{};
        
            oStringStream
                << user.GetId() << '\t'
                << user.GetName() << '\t'
                << user.GetPassword();
        
            return oStringStream.str();
        }
    }
    {
    }

    std::vector<User>::iterator UserRepository::GetByUserName(std::string_view userName)
    {
        std::vector<User>& entities{GetAll()};
        return std::ranges::find_if(entities, [userName](const User& item)
        {
            return item.GetName() == userName;
        });
    }

    std::vector<User> UserRepository::GetUsersByMessages(const std::vector<Messages::Message>& messages)
    {
        std::vector usersIds{
            SharedKernel::Select<Messages::Message, long>(
                messages, [](const Messages::Message& message)
                {
                    return message.GetUserId();
                })
        };
        SharedKernel::Distinct(usersIds);

        return Get(usersIds);
    }
}
