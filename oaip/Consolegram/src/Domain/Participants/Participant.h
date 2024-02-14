#pragma once
#include "../../SharedKernel/Entity.h"

namespace Consolegram::Domain::Participants
{
    class Participant : public SharedKernel::Entity
    {
        long _userId{};
        long _chatId{};
        bool _canWrite{};

    public:
        explicit Participant(long id, long userId, long chatId, bool canWrite);

        [[nodiscard]] long GetUserId() const;

        [[nodiscard]] long GetChatId() const;

        [[nodiscard]] long CanWrite() const;
    };
}