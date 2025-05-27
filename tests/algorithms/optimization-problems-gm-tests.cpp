#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <cstdint>
#include <numeric>

#include <optimization-problems-gm.hpp>

Fraction reduce(const Fraction& frac)
{
    uint8_t num = frac.first;
    uint8_t den = frac.second;
    if (den == 0)
        return {0, 1};  // just in case
    uint8_t g = std::gcd(num, den);
    return {static_cast<uint8_t>(num / g), static_cast<uint8_t>(den / g)};
}

bool fractionVectorsEqual(const FractionVector& a, const FractionVector& b)
{
    if (a.size() != b.size())
    {
        std::cerr << "Size mismatch: expected " << b.size() << ", got " << a.size() << "\n";
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i)
    {
        Fraction ra = reduce(a[i]);
        Fraction rb = reduce(b[i]);

        if (ra.first != rb.first || ra.second != rb.second)
        {
            std::cerr << "Mismatch at index " << i << ": expected " << static_cast<int>(rb.first) << "/"
                      << static_cast<int>(rb.second) << ", got " << static_cast<int>(ra.first) << "/"
                      << static_cast<int>(ra.second) << "\n";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////

TEST(KnapSackTest, FullItemsFit)
{
    ProfitWeightVector input = {{60, 10}, {100, 20}, {120, 30}};
    uint8_t capacity = 60;

    FractionVector expected = {{1, 1}, {1, 1}, {1, 1}};

    FractionVector result = fractionalKnapSackAlgorithm(input, capacity);
    EXPECT_TRUE(fractionVectorsEqual(result, expected));
}

TEST(KnapSackTest, PartialLastItem)
{
    ProfitWeightVector input = {{60, 10}, {100, 20}, {120, 30}};
    uint8_t capacity = 50;

    // Sorted order: 100/20 > 60/10 > 120/30
    // Should take item 1 full, item 0 full, item 2 2/3 (20+10+20)
    FractionVector expected = {{1, 1}, {1, 1}, {2, 3}};

    FractionVector result = fractionalKnapSackAlgorithm(input, capacity);
    EXPECT_TRUE(fractionVectorsEqual(result, expected));
}

TEST(KnapSackTest, NothingFits)
{
    ProfitWeightVector input = {{10, 50}, {20, 60}};
    uint8_t capacity = 10;

    FractionVector expected = {{0, 0}, {1, 6}};

    FractionVector result = fractionalKnapSackAlgorithm(input, capacity);
    EXPECT_TRUE(fractionVectorsEqual(result, expected));
}

TEST(KnapSackTest, FirstItemOnlyPartial)
{
    ProfitWeightVector input = {{30, 40}, {20, 50}};
    uint8_t capacity = 20;

    // Only part of the first item can fit
    FractionVector expected = {{1, 2}, {0, 1}};

    FractionVector result = fractionalKnapSackAlgorithm(input, capacity);
    EXPECT_TRUE(fractionVectorsEqual(result, expected));
}

TEST(KnapSackTest, EdgeCaseEmptyInput)
{
    ProfitWeightVector input = {};
    uint8_t capacity = 100;

    FractionVector expected = {};

    FractionVector result = fractionalKnapSackAlgorithm(input, capacity);
    EXPECT_TRUE(fractionVectorsEqual(result, expected));
}

///////////////////////////////////////////////////////////

int totalWeight(const WeightedEdgeList& edges)
{
    int total = 0;
    for (const auto& [u, v, w] : edges)
    {
        total += w;
    }
    return total;
}

TEST(KruskalTest, SimpleTriangle)
{
    WeightedEdgeList graph = {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}};

    auto mst = kruskalsMethod(graph, 3);

    EXPECT_EQ(mst.size(), 2);        // MST for 3 nodes should have 2 edges
    EXPECT_EQ(totalWeight(mst), 3);  // Edges (0,1) and (1,2)
}

TEST(KruskalTest, AlreadyMST)
{
    WeightedEdgeList graph = {{0, 1, 1}, {1, 2, 2}};

    auto mst = kruskalsMethod(graph, 3);

    EXPECT_EQ(mst.size(), 2);
    EXPECT_EQ(totalWeight(mst), 3);
}

TEST(KruskalTest, DisconnectedGraph)
{
    WeightedEdgeList graph = {{0, 1, 1}, {2, 3, 2}};

    auto mst = kruskalsMethod(graph, 4);

    EXPECT_EQ(mst.size(), 2);  // Two disjoint trees
    EXPECT_EQ(totalWeight(mst), 3);
}

TEST(KruskalTest, MultipleEqualWeightEdges)
{
    WeightedEdgeList graph = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 0, 5}};

    auto mst = kruskalsMethod(graph, 4);

    EXPECT_EQ(mst.size(), 3);        // MST should have 3 edges
    EXPECT_EQ(totalWeight(mst), 3);  // All weights = 1
}

TEST(KruskalTest, EmptyGraph)
{
    WeightedEdgeList graph;
    auto mst = kruskalsMethod(graph, 0);
    EXPECT_TRUE(mst.empty());
}

TEST(KruskalTest, SingleNode)
{
    WeightedEdgeList graph;
    auto mst = kruskalsMethod(graph, 1);
    EXPECT_TRUE(mst.empty());
}

TEST(KruskalTest, ComplexGraph)
{
    // Graph structure (undirected):
    //
    //       2
    //   0-------1
    //   |\     /|
    //  6| \4  / |3
    //   |  \ /  |
    //   3---2   4
    //    \  |  /
    //   5\ | /7
    //      5
    //
    // Edges: (u, v, weight)
    WeightedEdgeList graph = {{0, 1, 2}, {0, 3, 6}, {0, 2, 4}, {1, 2, 1}, {1, 4, 3},
                              {2, 3, 3}, {2, 5, 7}, {3, 5, 5}, {4, 5, 7}};

    auto mst = kruskalsMethod(graph, 6);

    EXPECT_EQ(mst.size(), 5);  // MST for 6 nodes should have 5 edges

    int expectedTotalWeight = 2 + 1 + 3 + 5 + 3;  // Chosen edges: (0-1), (1-2), (1-4), (3-5), (2-3)
    EXPECT_EQ(totalWeight(mst), expectedTotalWeight);
}

///////////////////////////////////////////////////////////

int countEdges(const AdjacencyMatrix& mst)
{
    int edgesCount = 0;
    for (int i = 0; i < (int)mst.size(); i++)
    {
        for (int j = i + 1; j < (int)mst[i].size(); j++)
        {
            if (mst[i][j] != 0)
            {
                edgesCount++;
            }
        }
    }

    return edgesCount;
}

int sumWeights(const AdjacencyMatrix& mst)
{
    int sumWeight = 0;
    for (int i = 0; i < (int)mst.size(); i++)
    {
        for (int j = i + 1; j < (int)mst[i].size(); j++)
        {
            if (mst[i][j] != 0)
            {
                sumWeight += mst[i][j];
            }
        }
    }
    return sumWeight;
}

AdjacencyMatrix makeAdjacencyMatrix(const WeightedEdgeList& graph, int numVertices)
{
    AdjacencyMatrix adj(numVertices, std::vector<int>(numVertices, 0));
    for (const auto& [u, v, w] : graph)
    {
        adj[u][v] = w;
        adj[v][u] = w;
    }
    return adj;
}

TEST(PrimTest, SimpleTriangle)
{
    WeightedEdgeList graph = {{0, 1, 1}, {1, 2, 2}, {0, 2, 3}};
    auto adj = makeAdjacencyMatrix(graph, 3);
    auto mst = primsMethod(adj);

    EXPECT_EQ(countEdges(mst), 2);
    EXPECT_EQ(sumWeights(mst), 3);
}

TEST(PrimTest, AlreadyMST)
{
    WeightedEdgeList graph = {{0, 1, 1}, {1, 2, 2}};
    auto adj = makeAdjacencyMatrix(graph, 3);
    auto mst = primsMethod(adj);

    EXPECT_EQ(countEdges(mst), 2);
    EXPECT_EQ(sumWeights(mst), 3);
}

TEST(PrimTest, MultipleEqualWeightEdges)
{
    WeightedEdgeList graph = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 0, 5}};
    auto adj = makeAdjacencyMatrix(graph, 4);
    auto mst = primsMethod(adj);

    EXPECT_EQ(countEdges(mst), 3);
    EXPECT_EQ(sumWeights(mst), 3);
}

TEST(PrimTest, EmptyGraph)
{
    AdjacencyMatrix adj;
    auto mst = primsMethod(adj);
    EXPECT_TRUE(mst.empty());
}

TEST(PrimTest, SingleNode)
{
    AdjacencyMatrix adj(1, std::vector<int>(1, 0));
    auto mst = primsMethod(adj);
    EXPECT_EQ(countEdges(mst), 0);
    EXPECT_EQ(sumWeights(mst), 0);
}

TEST(PrimTest, ComplexGraph)
{
    WeightedEdgeList graph = {{0, 1, 2}, {0, 3, 6}, {0, 2, 4}, {1, 2, 1}, {1, 4, 3},
                              {2, 3, 3}, {2, 5, 7}, {3, 5, 5}, {4, 5, 7}};
    auto adj = makeAdjacencyMatrix(graph, 6);
    auto mst = primsMethod(adj);

    EXPECT_EQ(countEdges(mst), 5);
    int expectedTotalWeight = 2 + 1 + 3 + 5 + 3;
    EXPECT_EQ(sumWeights(mst), expectedTotalWeight);
}

///////////////////////////////////////////////////////////

TEST(DijkstraTest, HandlesEmptyGraph)
{
    std::vector<std::vector<int>> emptyGraph;
    auto result = dijkstraMethod(emptyGraph, 0);
    EXPECT_TRUE(result.empty());
}

TEST(DijkstraTest, HandlesInvalidSource)
{
    std::vector<std::vector<int>> graph = {{0, 1}, {1, 0}};
    auto result = dijkstraMethod(graph, -1);
    EXPECT_TRUE(result.empty());

    result = dijkstraMethod(graph, 2);  // Out of bounds
    EXPECT_TRUE(result.empty());
}

TEST(DijkstraTest, SingleNodeGraph)
{
    std::vector<std::vector<int>> graph = {{0}};
    auto result = dijkstraMethod(graph, 0);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

TEST(DijkstraTest, SimpleGraph)
{
    /*
        Graph:
        0 --1--> 1
        0 --4--> 2
        1 --2--> 2
    */
    std::vector<std::vector<int>> graph = {{0, 1, 4}, {1, 0, 2}, {4, 2, 0}};

    auto result = dijkstraMethod(graph, 0);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 3);  // 0->1->2 = 1 + 2 = 3 (shorter than direct 4)
}

TEST(DijkstraTest, DisconnectedGraph)
{
    /*
        Graph:
        0 --1--> 1
        2 isolated
    */
    std::vector<std::vector<int>> graph = {{0, 1, 0}, {1, 0, 0}, {0, 0, 0}};

    auto result = dijkstraMethod(graph, 0);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], std::numeric_limits<int>::max());  // unreachable
}

TEST(DijkstraTest, ComplexCase)
{
    std::vector<std::vector<int>> graph = {
        {0, 1, 5, 0, 0, 0},  {1, 0, 3, 10, 8, 0}, {5, 3, 0, 0, 2, 0},
        {0, 10, 0, 0, 3, 2}, {0, 8, 2, 3, 0, 7},  {0, 0, 0, 2, 7, 0},
    };

    auto result = dijkstraMethod(graph, 0);
    ASSERT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 4);
    EXPECT_EQ(result[3], 9);
    EXPECT_EQ(result[4], 6);
    EXPECT_EQ(result[5], 11);
}
