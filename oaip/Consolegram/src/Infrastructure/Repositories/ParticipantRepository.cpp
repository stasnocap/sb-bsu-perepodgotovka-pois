#include "../../Domain/Participants/ParticipantRepository.h"

#include <sstream>

namespace Consolegram::Domain::Participants
{
    ParticipantRepository::ParticipantRepository(const SharedKernel::Config& config) : Repository{
        config["ParticipantsFileRelativePath"], [](std::ifstream& fileStream)
        {
            std::vector<Participant> participants{};

            long id{};
            long userId{};
            long chatId{};
            std::string canWrite{};

            while (!fileStream.eof())
            {
                fileStream >> id;
                fileStream >> userId;
                fileStream >> chatId;
                fileStream >> canWrite;

                participants.emplace_back(id, userId, chatId, canWrite == "true");
            }

            return participants;
        },
        [](const Participant& participant)
        {
            std::ostringstream oStringStream{};
        
            oStringStream
                << participant.GetId() << '\t'
                << participant.GetUserId() << '\t'
                << participant.GetChatId() << '\t'
                << participant.CanWrite();
        
            return oStringStream.str();
        }
    }
    {
    }

    std::vector<long> ParticipantRepository::GetChatsIds(long userId)
    {
        const std::vector<Participant>& participants{GetAll()};

        const std::vector filteredByUserId{
            SharedKernel::Where<Participant>(participants, [userId](const Participant& participant)
            {
                return participant.GetUserId() == userId;
            })
        };

        return SharedKernel::Select<Participant, long>(filteredByUserId, [](const Participant& participant)
        {
            return participant.GetChatId();
        });
    }
}
