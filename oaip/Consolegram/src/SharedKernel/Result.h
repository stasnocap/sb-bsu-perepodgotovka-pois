#pragma once
#include <string>

template <typename T>
class Result
{
    bool _success;
    T _value;
    std::string _error;

public:
    explicit Result(const bool success, const T& value, const std::string_view error)
        : _success{success}, _value{value}, _error{error}
    {
    }

    [[nodiscard]] bool IsSuccess() const
    {
        return _success;
    }

    [[nodiscard]] bool IsFailure() const
    {
        return !_success;
    }

    [[nodiscard]] T GetValue() const
    {
        return _value;
    }

    [[nodiscard]] std::string_view GetError() const
    {
        return _error;
    }

    static Result Success(const T& value)
    {
        return Result{true, value, ""};
    }

    static Result Failure(const std::string& errorMessage)
    {
        return Result{false, nullptr, errorMessage};
    }
};