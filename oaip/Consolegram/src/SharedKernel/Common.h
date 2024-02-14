#pragma once
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <vector>

namespace Consolegram::SharedKernel
{
    std::string GetString(std::string_view ask);

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
}
