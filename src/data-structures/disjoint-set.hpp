#pragma once

#include <graph.hpp>

/**
 * @class DisjointSet
 * @brief Implements a Disjoint Set Union (Union-Find) data structure with path compression.
 *
 * This data structure supports efficient union and find operations to keep track of
 * elements partitioned into disjoint sets.
 */
class DisjointSet
{
    std::vector<int> parent;

public:
    /**
     * @brief Constructs a DisjointSet with `n` elements, each in its own set initially.
     * @param n Number of elements (vertices).
     */
    DisjointSet(int n) : parent(n)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    /**
     * @brief Finds the representative (root) of the set containing element `x`.
     * @param x Element to find the set representative for.
     * @return int Representative (root) of the set containing `x`.
     */
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    /**
     * @brief Unites the sets containing elements `a` and `b`.
     * If `a` and `b` belong to different sets, merges them by making the root of `b` point to the root of `a`.
     * @param a First element.
     * @param b Second element.
     * @return true if successful, false otherwise.
     */
    bool unionSets(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA != rootB)
        {
            parent[rootB] = rootA;
            return true;
        }

        return false;
    }
};