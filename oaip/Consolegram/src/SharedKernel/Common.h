#pragma once
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <vector>

namespace Consolegram::SharedKernel::Common
{
    constexpr inline char ExitKey{'\n'};

    constexpr inline int ExitCode{-1};

    std::string GetString(std::string_view ask);

    std::string GetString(std::string_view ask, const std::function<bool(std::string_view)>& condition);

    int GetInt(std::string_view ask);

    int GetInt(std::string_view ask, const std::function<bool(int)>& condition);

    template <typename T>
    std::string ToLower(T& data)
    {
        std::string lower{data};
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](const unsigned char c) { return std::tolower(c); });
        return lower;
    }

    template <typename TEntity, typename TResult>
    std::vector<TResult> Select(const std::vector<TEntity>& entities,
                                const std::function<TResult(TEntity)>& selector)
    {
        std::vector<TResult> selects{};
        selects.reserve(entities.size());
        for (const TEntity& entity : entities)
        {
            selects.push_back(selector(entity));
        }
        return selects;
    }

    template <typename TEntity>
    std::vector<TEntity> Where(const std::vector<TEntity>& entities,
                               const std::function<bool(TEntity)>& predicate)
    {
        std::vector<TEntity> filtered{};
        std::copy_if(entities.begin(), entities.end(), std::back_inserter(filtered),
                     [&predicate](const TEntity& entity)
                     {
                         return predicate(entity);
                     });
        return filtered;
    }

    template <typename TEntity>
    void Distinct(std::vector<TEntity>& vector)
    {
        std::ranges::sort(vector);
        vector.erase(std::ranges::unique(vector).begin(), vector.end());
    }
}
