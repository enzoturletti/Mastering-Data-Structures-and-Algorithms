#include <gtest/gtest.h>
#include <graph.hpp>

///////////////////////////////////////////////////////////////////////////////////

// Adjacency Matrix Tests

TEST(AdjacencyMatrixTests, CreateAdjacencyMatrix)
{
    int numVertices = 3;
    AdjacencyMatrix matrix = createAdjacencyMatrix(numVertices);

    // Check if the matrix has the correct dimensions
    ASSERT_EQ(matrix.size(), numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
        ASSERT_EQ(matrix[i].size(), numVertices);
    }

    // Check if all elements are initialized to 0
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            ASSERT_EQ(matrix[i][j], 0);
        }
    }
}

TEST(AdjacencyMatrixTests, AddEdge)
{
    int numVertices = 3;
    AdjacencyMatrix matrix = createAdjacencyMatrix(numVertices);

    // Add an edge from vertex 0 to vertex 1
    addEdge(matrix, 0, 1);

    // Check if the edge was added correctly
    ASSERT_EQ(matrix[0][1], 1);
    ASSERT_EQ(matrix[1][0], 0);  // Ensure that no other edges were affected
}

TEST(AdjacencyMatrixTests, CheckEdge)
{
    int numVertices = 3;
    AdjacencyMatrix matrix = createAdjacencyMatrix(numVertices);

    // Add an edge from vertex 0 to vertex 1
    addEdge(matrix, 0, 1);

    // Check if the edge exists
    ASSERT_TRUE(checkEdge(matrix, 0, 1));
    ASSERT_FALSE(checkEdge(matrix, 1, 0));  // Ensure that reverse edge does not exist
}

TEST(AdjacencyMatrixTests, RemoveEdge)
{
    int numVertices = 3;
    AdjacencyMatrix matrix = createAdjacencyMatrix(numVertices);

    // Add and then remove an edge
    addEdge(matrix, 0, 1);
    removeEdge(matrix, 0, 1);

    // Ensure the edge was removed
    ASSERT_FALSE(checkEdge(matrix, 0, 1));
}

///////////////////////////////////////////////////////////////////////////////////

// Adjacency List Tests

TEST(AdjacencyListTests, CreateAdjacencyList)
{
    int numVertices = 3;
    AdjacencyList adjList = createAdjacencyList(numVertices);

    // Check if the adjacency list has the correct number of vertices
    ASSERT_EQ(adjList.size(), numVertices);

    // Check if all lists are initially empty
    for (const auto& neighbors : adjList)
    {
        ASSERT_TRUE(neighbors.empty());
    }
}

TEST(AdjacencyListTests, AddEdge)
{
    int numVertices = 3;
    AdjacencyList adjList = createAdjacencyList(numVertices);

    // Add an edge from vertex 0 to vertex 1
    addEdge(adjList, 0, 1);

    // Check if the edge was added correctly
    ASSERT_TRUE(checkEdge(adjList, 0, 1));
    ASSERT_FALSE(checkEdge(adjList, 1, 0));  // Ensure that reverse edge does not exist
}

TEST(AdjacencyListTests, CheckEdge)
{
    int numVertices = 3;
    AdjacencyList adjList = createAdjacencyList(numVertices);

    // Add an edge from vertex 0 to vertex 1
    addEdge(adjList, 0, 1);

    // Check if the edge exists
    ASSERT_TRUE(checkEdge(adjList, 0, 1));
    ASSERT_FALSE(checkEdge(adjList, 1, 0));  // Ensure that reverse edge does not exist
}

TEST(AdjacencyListTests, RemoveEdge)
{
    int numVertices = 3;
    AdjacencyList adjList = createAdjacencyList(numVertices);

    // Add and then remove an edge
    addEdge(adjList, 0, 1);
    removeEdge(adjList, 0, 1);

    // Ensure the edge was removed
    ASSERT_FALSE(checkEdge(adjList, 0, 1));
}

///////////////////////////////////////////////////////////////////////////////////

// Edge List Tests

TEST(EdgeListTests, CreateEdgeList)
{
    EdgeList edgeList = createEdgeList();

    // Check if the edge list is initially empty
    ASSERT_TRUE(edgeList.empty());
}

TEST(EdgeListTests, AddEdge)
{
    EdgeList edgeList = createEdgeList();

    // Add an edge from vertex 0 to vertex 1
    addEdge(edgeList, 0, 1);

    // Check if the edge was added correctly
    ASSERT_EQ(edgeList.size(), 1);
    ASSERT_EQ(edgeList[0].first, 0);
    ASSERT_EQ(edgeList[0].second, 1);
}

TEST(EdgeListTests, CheckEdge)
{
    EdgeList edgeList = createEdgeList();

    // Add an edge from vertex 0 to vertex 1
    addEdge(edgeList, 0, 1);

    // Check if the edge exists
    ASSERT_TRUE(checkEdge(edgeList, 0, 1));
    ASSERT_FALSE(checkEdge(edgeList, 1, 0));  // Ensure that reverse edge does not exist
}

TEST(EdgeListTests, RemoveEdge)
{
    EdgeList edgeList = createEdgeList();

    // Add and then remove an edge
    addEdge(edgeList, 0, 1);
    removeEdge(edgeList, 0, 1);

    // Ensure the edge was removed
    ASSERT_FALSE(checkEdge(edgeList, 0, 1));
}

///////////////////////////////////////////////////////////////////////////////////

// BFS Tests

TEST(BFSTests, SingleComponentGraph)
{
    AdjacencyList graph = createAdjacencyList(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);

    std::vector<int> visitOrder;
    BFS(graph, [&](int v) {
        visitOrder.push_back(v);
        return false;
    });

    // Check that all nodes are visited and BFS order starts from 0
    std::vector<int> expected = {0, 1, 2, 3, 4};
    ASSERT_EQ(visitOrder.size(), expected.size());
    for (int v : expected)
    {
        ASSERT_NE(std::find(visitOrder.begin(), visitOrder.end(), v), visitOrder.end());
    }
}

TEST(BFSTests, DisconnectedGraph)
{
    AdjacencyList graph = createAdjacencyList(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 3, 4);

    std::vector<int> visitOrder;
    BFS(graph, [&](int v) {
        visitOrder.push_back(v);
        return false;
    });

    // Check all nodes are visited (components: {0,1,2}, {3,4}, {5})
    std::vector<int> expected = {0, 1, 2, 3, 4, 5};
    std::sort(visitOrder.begin(), visitOrder.end());
    ASSERT_EQ(visitOrder, expected);
}

TEST(BFSTests, EmptyGraph)
{
    AdjacencyList graph;
    std::vector<int> visitOrder;
    BFS(graph, [&](int v) {
        visitOrder.push_back(v);
        return false;
    });
    ASSERT_TRUE(visitOrder.empty());
}

TEST(BFSTests, VisitEarlyStop)
{
    // Graph: 0->1->2
    AdjacencyList graph(3);
    graph[0].push_back(1);
    graph[1].push_back(2);

    int visitedCount = 0;
    BFS(graph, [&](int node) {
        visitedCount++;
        return visitedCount == 1;  // Stop after visiting first node
    });

    ASSERT_EQ(visitedCount, 1);
}

///////////////////////////////////////////////////////////////////////////////////

// DFS Tests

std::vector<int> collectDFS(const std::vector<std::list<int>>& graph)
{
    std::vector<int> visitedNodes;
    DFS(graph, [&](int node) {
        visitedNodes.push_back(node);
        return false;  // continue traversal
    });
    return visitedNodes;
}

TEST(DFSTests, EmptyGraph)
{
    AdjacencyList graph;
    auto visited = collectDFS(graph);
    ASSERT_TRUE(visited.empty());
}

TEST(DFSTests, SingleNodeGraph)
{
    AdjacencyList graph(1);
    auto visited = collectDFS(graph);
    ASSERT_EQ(visited.size(), 1);
    ASSERT_EQ(visited[0], 0);
}

TEST(DFSTests, SimpleGraph)
{
    // Graph:
    // 0 -> 1, 2
    // 1 -> 2
    // 2 -> (no edges)
    AdjacencyList graph(3);
    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(2);

    auto visited = collectDFS(graph);

    // DFS order could be [0,2,1] or [0,1,2] depending on stack order
    // Since we push neighbors in reverse order, expected: 0,1,2
    std::vector<int> expected = {0, 1, 2};
    ASSERT_EQ(visited, expected);
}

TEST(DFSTests, DisconnectedGraph)
{
    // Graph with two components:
    // 0 -> 1
    // 2 isolated
    AdjacencyList graph(3);
    graph[0].push_back(1);

    auto visited = collectDFS(graph);

    // All nodes visited, order: 0,1,2
    std::vector<int> expected = {0, 1, 2};
    ASSERT_EQ(visited, expected);
}

TEST(DFSTests, VisitEarlyStop)
{
    // Graph: 0->1->2
    AdjacencyList graph(3);
    graph[0].push_back(1);
    graph[1].push_back(2);

    int visitedCount = 0;
    DFS(graph, [&](int node) {
        visitedCount++;
        return true;  // Stop after visiting first node
    });

    ASSERT_EQ(visitedCount, 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
