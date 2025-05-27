#pragma once

#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>
#include <graph.hpp>
#include <limits>

/*
Optimization problems involve finding the best solution — either maximizing or minimizing
an objective — while satisfying specific constraints.

Example:
Choosing a smartphone with the highest possible storage capacity (objective),
within a budget limit of $25,000 (constraint).
*/

/*
Greedy Algorithm Framework

The Greedy Method builds a solution piece by piece, always choosing the option that looks
best at the moment (locally optimal), with the hope that this leads to a globally optimal solution.

Algorithm GreedyMethod(Elements)
{
    Solution = empty set;

    for (i = 1 to ElementsSize)
    {
        x = Select(Elements); // Choose the next best candidate based on the objective.

        if (Feasible(x))      // Check if adding x violates any constraints.
        {
            Solution = Solution ∪ {x}; // Include x in the solution set.
        }
    }

    return Solution;
}
*/

////////////////////// FRACTIONAL KNAPSACK ////////////////////////////

using ProfitWeight = std::pair<uint8_t, uint8_t>;
using ProfitWeightVector = std::vector<ProfitWeight>;
using Fraction = std::pair<uint8_t, uint8_t>;  // numerator, denominator
using FractionVector = std::vector<Fraction>;

/**
 * @brief Solves the fractional knapsack problem using a greedy strategy.
 *
 * This function receives a list of items defined by their profit and weight,
 * and a total bag capacity. It selects items (or fractions of them) to maximize
 * profit-to-weight ratio. The result is a vector of fractions indicating how much
 * of each original item is included in the optimal solution.
 *
 * @param input A vector of pairs where each pair represents an item:
 *        - first: the profit (uint8_t)
 *        - second: the weight (uint8_t)
 * @param bagCapacity The maximum capacity of the knapsack (uint8_t).
 *
 * @return A vector of fractions (pairs of uint8_t) corresponding to each input item,
 *         indicating how much of that item is included in the knapsack. Each fraction
 *         is of the form {numerator, denominator}, meaning (numerator / denominator).
 *
 * @note The input vector must not contain items with zero weight (asserted).
 *       The output vector is in the same order as the input.
 *
 * @throws Assertion failure if any item's weight is zero.
 *
 * @complexity
 * Time Complexity: O(N * log N)
 *   - O(N) to build the enriched structure (IndexedItem)
 *   - O(N * log N) to sort by profit/weight ratio
 *   - O(N) to iterate and fill the solution
 *
 * Space Complexity: O(N)
 *   - O(N) for the auxiliary `items` vector
 *   - O(N) for the output `solution` vector
 */
FractionVector fractionalKnapSackAlgorithm(const ProfitWeightVector& input, uint8_t bagCapacity)
{
    struct IndexedItem
    {
        uint8_t profit;
        uint8_t weight;
        size_t index;  // original index
    };

    std::vector<IndexedItem> items;
    for (size_t i = 0; i < input.size(); ++i)
    {
        const auto& [profit, weight] = input[i];
        assert(weight != 0);
        items.push_back({profit, weight, i});
    }

    // Sort by profit/weight ratio in descending order
    std::sort(items.begin(), items.end(), [](const IndexedItem& a, const IndexedItem& b) {
        return static_cast<uint16_t>(a.profit) * b.weight > static_cast<uint16_t>(b.profit) * a.weight;
    });

    // Temporary storage for fractions with original indices
    std::vector<Fraction> solution(input.size(), {0, 1});
    uint8_t currentWeight = 0;

    for (const auto& item : items)
    {
        if (currentWeight + item.weight <= bagCapacity)
        {
            // Take full item
            currentWeight += item.weight;
            solution[item.index] = {1, 1};
        }
        else
        {
            uint8_t remaining = bagCapacity - currentWeight;

            if (remaining > 0)
            {
                solution[item.index] = {remaining, item.weight};  // fraction of item
                currentWeight += remaining;
            }

            break;  // bag is full
        }
    }

    return solution;
}

///////////////////////////////////////////////////////////

////////////////////// Minimum cost Spanning Tree ////////////////////////////

// A Spanning Tree is a subgraph of an undirected, connected graph that satisfies the following:
// 1. Includes all the vertices of the original graph.
// 2. Contains exactly (V - 1) edges, where V is the number of vertices.
// 3. Has no cycles — it is minimally connected.

/**
 * @brief Computes the Minimum Spanning Tree (MST) of a weighted undirected graph using Kruskal's algorithm.
 *
 * This function sorts all the edges by ascending weight and then uses a Disjoint Set (Union-Find)
 * to select edges that do not form a cycle, building an MST incrementally.
 *
 * @param graph A list of edges represented as tuples (u, v, weight).
 * @param numVertices The total number of vertices in the graph.
 * @return WeightedEdgeList The list of edges that form the MST.
 */
WeightedEdgeList kruskalsMethod(WeightedEdgeList& graph, int numVertices)
{
    // Step 1: Sort all edges in non-decreasing order by weight
    std::sort(graph.begin(), graph.end(), [](const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    // Step 2: Create a Disjoint Set to track connected components
    DisjointSet ds(numVertices);  // Single Disjoint Set
    WeightedEdgeList result;

    // Step 3: Iterate through sorted edges
    for (const auto& [u, v, weight] : graph)
    {
        if (ds.unionSets(u, v))  // If union is successful (no cycle), add edge
        {
            result.emplace_back(u, v, weight);
        }
    }

    // Step 4: Return the edges that form the Minimum Spanning Tree
    return result;
}

/**
 * @brief Computes the Minimum Spanning Tree (MST) of a weighted undirected graph using Prim's algorithm.
 *
 * This implementation uses an adjacency matrix representation of the graph.
 * It starts from vertex 0 and incrementally adds the minimum weight edge connecting
 * a vertex inside the MST to a vertex outside the MST, until all vertices are included or no
 * connecting edge exists (disconnected graph).
 *
 * @param graph The input graph represented as an adjacency matrix, where graph[i][j] is the weight of the edge
 *              between vertices i and j (0 if no edge).
 * @return AdjacencyMatrix The adjacency matrix representation of the MST, with weights of edges included in the MST.
 *                        Edges not in the MST have weight 0.
 */
AdjacencyMatrix primsMethod(const AdjacencyMatrix& graph)
{
    if (graph.empty() || graph[0].empty())
    {
        return AdjacencyMatrix();
    }

    int numVertices = (int)graph.size();
    AdjacencyMatrix result(
        numVertices, std::vector<int>(numVertices, 0));  // MST adjacency matrix with zero weights initially

    std::vector<bool> inMST(numVertices, false);  // track included vertices
    inMST[0] = true;                              // start from vertex 0

    // Keep track of vertices included so far
    std::vector<int> verticesInMST = {0};

    // Number of edges added to MST so far
    int edgesAdded = 0;

    while (edgesAdded < numVertices - 1)
    {
        int minWeight = std::numeric_limits<int>::max();
        int u = -1;  // vertex in MST
        int v = -1;  // vertex not yet in MST

        // Search for the minimum edge connecting MST to outside
        for (int from : verticesInMST)
        {
            for (int to = 0; to < numVertices; ++to)
            {
                // If 'to' is not in MST and edge exists with weight > 0
                if (!inMST[to] && graph[from][to] > 0 && graph[from][to] < minWeight)
                {
                    minWeight = graph[from][to];
                    u = from;
                    v = to;
                }
            }
        }

        if (v == -1)
        {
            break;
        }

        // Add edge (u, v) to MST
        result[u][v] = minWeight;
        result[v][u] = minWeight;

        inMST[v] = true;
        verticesInMST.push_back(v);
        edgesAdded++;
    }

    return result;
}

///////////////////////////////////////////////////////////

////////////////////// Single Source Shortest Path (Dijkstra) ////////////////////////////

std::vector<int> dijkstraMethod(const AdjacencyMatrix& graph, int source)
{
    const int INF{std::numeric_limits<int>::max()};

    if (graph.empty() || source < 0 || source >= graph.size())
    {
        return {};
    }

    std::vector<int> distances(graph.size(), INF);
    std::vector<bool> visited(graph.size(), false);
    distances[source] = 0;

    int visitedCount = 0;

    int selected = source;
    while (visitedCount < graph.size())
    {
        if (!visited[selected])
        {
            visited[selected] = true;
            visitedCount++;
        }

        // Relax neighbors
        for (int i = 0; i < graph[selected].size(); i++)
        {
            if (!visited[i] && graph[selected][i] > 0)
            {
                int newDistance = distances[selected] + graph[selected][i];
                if (newDistance < distances[i])
                {
                    distances[i] = newDistance;
                }
            }
        }

        // Select next unvisited node with smallest tentative distance
        int minDistance = INF;
        for (int i = 0; i < distances.size(); i++)
        {
            if (!visited[i] && distances[i] < minDistance)
            {
                minDistance = distances[i];
                selected = i;
            }
        }

        if (minDistance == INF)
        {
            break;  // Remaining nodes are unreachable
        }
    }

    return distances;
}

///////////////////////////////////////////////////////////
