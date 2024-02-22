#pragma once
#include <string_view>
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Chats
{
    class Chat final : public SharedKernel::Entity
    {
        std::string _name{};

    public:
        explicit Chat(long id, std::string name);

        [[nodiscard]] std::string_view GetName() const;
    };
}