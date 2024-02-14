#pragma once

namespace Consolegram::SharedKernel
{
    class Entity
    {
        long _id{};

    public:
        explicit Entity(long id);

        [[nodiscard]] long GetId() const;
    };
}