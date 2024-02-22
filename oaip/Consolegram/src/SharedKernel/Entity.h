#pragma once
#include <string_view>

namespace Consolegram::SharedKernel
{
    class Entity
    {
    protected:
        explicit Entity(long id);
        virtual ~Entity() = default;

    private:
        long _id{};

    public:
        [[nodiscard]] long GetId() const;
        
        [[nodiscard]] virtual std::string ToFileString() const = 0;
    };
}
