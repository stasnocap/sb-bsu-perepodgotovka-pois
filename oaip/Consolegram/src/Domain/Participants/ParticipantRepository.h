#pragma once

#include <vector>
#include "Participant.h"
#include "../../SharedKernel/Config.h"
#include "../../SharedKernel/Repository.h"

namespace Consolegram::Domain::Participants
{
    class ParticipantRepository : public SharedKernel::Repository<Participant>
    {
    public:
        explicit ParticipantRepository(const SharedKernel::Config& config);

        std::vector<long> GetChatsIds(long userId);
    };
}