#include "Participant.h"

#include <sstream>

namespace Consolegram::Domain::Participants
{
    Participant::Participant(const long id, const long userId, const long chatId, const bool canWrite)
        : Entity(id), _userId{userId}, _chatId{chatId}, _canWrite{canWrite}
    {
    }

    long Participant::GetUserId() const
    {
        return _userId;
    }

    long Participant::GetChatId() const
    {
        return _chatId;
    }

    bool Participant::CanWrite() const
    {
        return _canWrite;
    }
}
