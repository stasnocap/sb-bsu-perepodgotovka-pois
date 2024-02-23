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
            SharedKernel::Common::Where<Participant>(participants, [userId](const Participant& participant)
            {
                return participant.GetUserId() == userId;
            })
        };

        return SharedKernel::Common::Select<Participant, long>(filteredByUserId, [](const Participant& participant)
        {
            return participant.GetChatId();
        });
    }

    bool ParticipantRepository::CanWrite(const long userId, const long chatId)
    {
        const std::vector<Participant>& participants{GetAll()};

        const auto participant{
            std::ranges::find_if(participants, [userId, chatId](const Participant& participant)
            {
                return participant.GetUserId() == userId && participant.GetChatId() == chatId;
            })
        };

        if (participant == End())
        {
            throw std::invalid_argument(std::format("Participant with userId({}) and chatId({}) was not found", userId, chatId));
        }

        return participant->CanWrite();
    }
}
