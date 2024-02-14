#pragma once

namespace Consolegram::SharedKernel
{
    namespace ChangeType
    {
        enum ChangeType
        {
            None,
            Add,
            Remove,
            Update,
        };
    }

    template <typename T>
    struct Change
    {
        ChangeType::ChangeType Type{};
        T Value{};
    };
}