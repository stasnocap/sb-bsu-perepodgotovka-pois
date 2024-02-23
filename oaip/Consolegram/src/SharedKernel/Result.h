#pragma once

#include <string>

namespace Consolegram::SharedKernel
{
    class Result
    {
        bool _success;
        std::string _error;

    protected:
        explicit Result(bool success, std::string_view error);

    public:
        [[nodiscard]] bool IsSuccess() const;

        [[nodiscard]] bool IsFailure() const;

        [[nodiscard]] std::string_view GetError() const;

        static Result Success();

        static Result Failure(const std::string& errorMessage);
    };
}
