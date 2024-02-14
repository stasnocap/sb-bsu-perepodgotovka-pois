#include "Participant.h"

namespace Consolegram::Domain::Participants
{
    Participant::Participant(const long id, const long userId, const long chatId, const bool canWrite)
        : SharedKernel::Entity(id), _userId{userId}, _chatId{chatId}, _canWrite{canWrite}
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

    long Participant::CanWrite() const
    {
        return _canWrite;
    }
}
