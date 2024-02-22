#include "Entity.h"

namespace Consolegram::SharedKernel
{
    Entity::Entity(const long id) : _id{id}
    {
    }

    long Entity::GetId() const
    {
        return _id;
    }
}
