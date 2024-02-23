#include "Result.h"

namespace Consolegram::SharedKernel
{
    Result::Result(const bool success, const std::string_view error) : _success{success}, _error{error}
    {
    }

    bool Result::IsSuccess() const
    {
        return _success;
    }

    bool Result::IsFailure() const
    {
        return !_success;
    }

    std::string_view Result::GetError() const
    {
        return _error;
    }

    Result Result::Success()
    {
        return Result{true, ""};
    }

    Result Result::Failure(const std::string& errorMessage)
    {
        return Result{false, errorMessage};
    }
}