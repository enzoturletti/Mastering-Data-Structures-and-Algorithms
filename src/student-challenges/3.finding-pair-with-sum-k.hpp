#pragma once

#include <dynamic-array.hpp>
#include <optional>
#include <unordered_map>

template <typename Iterator>
[[nodiscard]] std::optional<DynamicArray<DynamicArray<int>>> findingPairWithSumK(Iterator begin, Iterator end, int k)
{
    if (begin == end)
    {
        return std::nullopt;
    }

    DynamicArray<DynamicArray<int>> results;

    // Count each value in the container. ~ Time: O(n)
    std::unordered_map<int, int> count;

    for (Iterator it = begin; it != end; it++)
    {
        const int complement = k - *it;
        const int countComplement = count[complement];
        for (int i = 0; i < countComplement; i++)
        {
            if (*it < complement)
            {
                results.append({*it, complement});
            }
            else
            {
                results.append({complement, *it});
            }
        }
        count[*it]++;
    }

    if (results.getSize() == 0)
    {
        return std::nullopt;
    }

    return results;
}