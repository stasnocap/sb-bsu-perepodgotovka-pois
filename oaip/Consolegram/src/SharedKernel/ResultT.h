#pragma once

#include "Result.h"

namespace Consolegram::SharedKernel
{
    template <typename T>
    class ResultT : public Result
    {
        T _value;

    public:
        explicit ResultT(const bool success, const T& value, const std::string_view error)
            : Result{success, error}, _value{value}
        {
        }
        
        [[nodiscard]] T GetValue() const
        {
            return _value;
        }

        static ResultT Success(const T& value)
        {
            return ResultT{true, value, ""};
        }

        static ResultT Failure(const std::string& errorMessage)
        {
            return ResultT{false, nullptr, errorMessage};
        }
    };
}