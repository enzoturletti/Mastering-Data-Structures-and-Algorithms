#pragma once

#include <functional>
#include <list>
#include <queue>
#include <stack>
#include <stdexcept>  // for std::out_of_range
#include <utility>
#include <vector>
#include <tuple>
#include <disjoint-set.hpp>

///////////////////////////////////////////////////////////////////////////////////

// Adjacency Matrix representation

using AdjacencyMatrix = std::vector<std::vector<int>>;

/**
 * @brief Creates an adjacency matrix for a graph with the given number of vertices.
 *
 * This function initializes a 2D vector (adjacency matrix) of size `numberOfVertex x numberOfVertex`.
 * All values in the matrix are initialized to zero, indicating that there are no edges between the vertices initially.
 *
 * @param numberOfVertex The number of vertices in the graph.
 * @return AdjacencyMatrix A 2D matrix representing the adjacency matrix of the graph.
 *
 * @note The adjacency matrix is typically used to represent a graph where the element at
 *       matrix[i][j] is non-zero (often 1) if there is an edge from vertex i to vertex j.
 *
 * @complexity
 *  - Time Complexity: O(V^2), where V is the number of vertices (numberOfVertex). This is because
 *    the adjacency matrix is initialized as a 2D vector with V rows and V columns, resulting in a
 *    nested loop to initialize each element.
 *  - Space Complexity: O(V^2), as we are using a 2D vector to store the adjacency matrix.
 */
AdjacencyMatrix createAdjacencyMatrix(int numberOfVertex)
{
    // Create a 2D vector (matrix) with dimensions numberOfVertex x numberOfVertex
    // All elements are initialized to 0, representing no edges between vertices
    AdjacencyMatrix matrix(numberOfVertex, std::vector<int>(numberOfVertex, 0));

    return matrix;
}

/**
 * @brief Adds an edge from one vertex to another in the adjacency matrix.
 *
 * This function modifies the adjacency matrix by setting the matrix element at [fromVertex][toVertex]
 * to 1, representing the existence of a directed edge from `fromVertex` to `toVertex`.
 *
 * @param matrix The adjacency matrix of the graph (passed by reference to modify it).
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 *
 * @complexity
 *  - Time Complexity: O(1), as setting a value in a vector by index is a constant-time operation.
 *  - Space Complexity: O(1), as we are only modifying the existing matrix, no additional space is used.
 */
void addEdge(AdjacencyMatrix& matrix, int fromVertex, int toVertex)
{
    // Set the element at [fromVertex][toVertex] to 1 to indicate an edge
    matrix[fromVertex][toVertex] = 1;
}

/**
 * @brief Checks if there is an edge between two vertices in the adjacency matrix.
 *
 * This function checks if there is a directed edge from `fromVertex` to `toVertex` by looking at
 * the matrix element at [fromVertex][toVertex].
 *
 * @param matrix The adjacency matrix of the graph.
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 * @return true If there is an edge from `fromVertex` to `toVertex`.
 * @return false If there is no edge from `fromVertex` to `toVertex`.
 *
 * @complexity
 *  - Time Complexity: O(1), as checking a value in a vector by index is a constant-time operation.
 *  - Space Complexity: O(1), as we are not using any additional space.
 */
bool checkEdge(const AdjacencyMatrix& matrix, int fromVertex, int toVertex)
{
    return matrix[fromVertex][toVertex] == 1;
}

/**
 * @brief Removes an edge from the adjacency matrix by setting the matrix element to 0.
 *
 * This function removes the directed edge from `fromVertex` to `toVertex` by setting the matrix element
 * at [fromVertex][toVertex] to 0.
 *
 * @param matrix The adjacency matrix of the graph (passed by reference to modify it).
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 *
 * @complexity
 *  - Time Complexity: O(1), as setting a value in a vector by index is a constant-time operation.
 *  - Space Complexity: O(1), as we are only modifying the existing matrix, no additional space is used.
 */
void removeEdge(AdjacencyMatrix& matrix, int fromVertex, int toVertex)
{
    // Set the element at [fromVertex][toVertex] to 0 to remove the edge
    matrix[fromVertex][toVertex] = 0;
}

///////////////////////////////////////////////////////////////////////////////////

// Adjacency List representation

// Alias for adjacency list representation
using AdjacencyList = std::vector<std::list<int>>;
using WeightAdjacencyList = std::vector<std::list<std::tuple<int, int>>>;

/**
 * @brief Creates an adjacency list for a graph with the given number of vertices.
 *
 * This function initializes a vector of lists, where each list represents the neighbors of a vertex.
 * Initially, all lists are empty, indicating that no edges exist.
 *
 * @param numberOfVertex The number of vertices in the graph.
 * @return AdjacencyList A vector of lists, each representing a vertex's neighbors.
 *
 * @note In an adjacency list, each element in the vector contains a list of vertices that are adjacent
 *       to the corresponding vertex (i.e., there are edges from the vertex to each vertex in its list).
 *
 * @complexity
 *  - Time Complexity: O(V), where V is the number of vertices (numberOfVertex). This is because we initialize
 *    a vector of `V` lists, which is a linear operation.
 *  - Space Complexity: O(V), as we only store the adjacency lists themselves.
 */
AdjacencyList createAdjacencyList(int numberOfVertex)
{
    // Create a vector of lists, with each list representing the neighbors of a vertex
    // Initially, all lists are empty, as no edges exist
    AdjacencyList adjList(numberOfVertex);
    return adjList;
}

/**
 * @brief Adds an edge from one vertex to another in the adjacency list.
 *
 * This function modifies the adjacency list by adding the target vertex to the source vertex's list,
 * representing the existence of a directed edge from `fromVertex` to `toVertex`.
 *
 * @param adjList The adjacency list of the graph (passed by reference to modify it).
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 *
 * @complexity
 *  - Time Complexity: O(1), as adding an element to the list is a constant-time operation.
 *  - Space Complexity: O(1), as we are only modifying the existing adjacency list, no additional space is used.
 */
void addEdge(AdjacencyList& adjList, int fromVertex, int toVertex)
{
    // Add the target vertex to the source vertex's list of neighbors
    adjList[fromVertex].push_back(toVertex);
}

/**
 * @brief Checks if there is an edge between two vertices in the adjacency list.
 *
 * This function checks if there is a directed edge from `fromVertex` to `toVertex` by checking
 * if `toVertex` exists in the list of neighbors for `fromVertex`.
 *
 * @param adjList The adjacency list of the graph.
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 * @return true If there is an edge from `fromVertex` to `toVertex`.
 * @return false If there is no edge from `fromVertex` to `toVertex`.
 *
 * @complexity
 *  - Time Complexity: O(V), where V is the number of neighbors for the `fromVertex`. In the worst case,
 *    we may need to check all neighbors of the `fromVertex` to see if `toVertex` exists.
 *  - Space Complexity: O(1), as we are only checking the list without using additional space.
 */
bool checkEdge(const AdjacencyList& adjList, int fromVertex, int toVertex)
{
    // Check if toVertex exists in the list of neighbors for fromVertex
    for (int neighbor : adjList[fromVertex])
    {
        if (neighbor == toVertex)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Removes an edge from the adjacency list by removing `toVertex` from the list of `fromVertex`.
 *
 * This function removes the directed edge from `fromVertex` to `toVertex` by removing `toVertex` from the
 * list of neighbors for `fromVertex`.
 *
 * @param adjList The adjacency list of the graph (passed by reference to modify it).
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 *
 * @complexity
 *  - Time Complexity: O(V), where V is the number of neighbors for `fromVertex`. In the worst case, we may
 *    need to traverse the entire list to remove `toVertex`.
 *  - Space Complexity: O(1), as we are only modifying the existing list, no additional space is used.
 */
void removeEdge(AdjacencyList& adjList, int fromVertex, int toVertex)
{
    // Find and remove the target vertex from the list of neighbors for fromVertex
    adjList[fromVertex].remove(toVertex);
}

///////////////////////////////////////////////////////////////////////////////////

// Edge List representation
using EdgeList = std::vector<std::pair<int, int>>;
using WeightedEdgeList = std::vector<std::tuple<int, int, int>>;  // (u, v, weight)

/**
 * @brief Creates an edge list for a graph with the given number of vertices.
 *
 * This function initializes a vector of pairs, where each pair represents an edge in the graph.
 * Initially, the edge list is empty, meaning no edges exist.
 *
 * @return EdgeList A vector of pairs, where each pair represents an edge.
 *
 * @note In an edge list, each element in the vector is a pair of integers (fromVertex, toVertex),
 *       representing a directed edge from `fromVertex` to `toVertex`.
 *
 * @complexity
 *  - Time Complexity: O(1), as the edge list is initialized as an empty vector.
 *  - Space Complexity: O(E), where E is the number of edges, as space is allocated dynamically
 *    for each edge added to the list.
 */
EdgeList createEdgeList()
{
    // Initialize an empty edge list
    EdgeList edgeList;

    return edgeList;
}

/**
 * @brief Adds an edge to the edge list.
 *
 * This function modifies the edge list by adding a pair representing an edge between `fromVertex` and `toVertex`.
 *
 * @param edgeList The edge list of the graph (passed by reference to modify it).
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 *
 * @complexity
 *  - Time Complexity: O(1), as adding an element to the vector is a constant-time operation.
 *  - Space Complexity: O(1), as we are only modifying the existing edge list, no additional space is used.
 */
void addEdge(EdgeList& edgeList, int fromVertex, int toVertex)
{
    // Add a pair representing the edge from fromVertex to toVertex
    edgeList.push_back(std::make_pair(fromVertex, toVertex));
}

/**
 * @brief Checks if there is an edge between two vertices in the edge list.
 *
 * This function checks if there is a directed edge from `fromVertex` to `toVertex` by searching the edge list
 * for a pair representing that edge.
 *
 * @param edgeList The edge list of the graph.
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 * @return true If there is an edge from `fromVertex` to `toVertex`.
 * @return false If there is no edge from `fromVertex` to `toVertex`.
 *
 * @complexity
 *  - Time Complexity: O(E), where E is the number of edges, as we need to check each edge in the list.
 *  - Space Complexity: O(1), as we are only searching within the existing edge list without using extra space.
 */
bool checkEdge(const EdgeList& edgeList, int fromVertex, int toVertex)
{
    // Search through the edge list for the edge from fromVertex to toVertex
    for (const auto& edge : edgeList)
    {
        if (edge.first == fromVertex && edge.second == toVertex)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Removes an edge from the edge list by finding and removing the pair representing it.
 *
 * This function removes the directed edge from `fromVertex` to `toVertex` by finding and removing the corresponding
 * pair in the edge list.
 *
 * @param edgeList The edge list of the graph (passed by reference to modify it).
 * @param fromVertex The index of the source vertex (the vertex where the edge originates).
 * @param toVertex The index of the target vertex (the vertex where the edge points to).
 *
 * @complexity
 *  - Time Complexity: O(E), where E is the number of edges, as we need to search through the edge list
 *    to find and remove the pair.
 *  - Space Complexity: O(1), as we are only modifying the existing edge list, no additional space is used.
 */
void removeEdge(EdgeList& edgeList, int fromVertex, int toVertex)
{
    // Find and remove the edge from the edge list
    auto it = std::remove(edgeList.begin(), edgeList.end(), std::make_pair(fromVertex, toVertex));
    edgeList.erase(it, edgeList.end());
}

/**
 * @brief Checks whether the given weighted graph contains a cycle.
 *
 * Uses a Disjoint Set data structure to detect cycles by checking if two vertices
 * of an edge are already connected.
 *
 * @param numVertices Number of vertices in the graph.
 * @param edges A list of edges, where each edge is a tuple (u, v, weight).
 * @return true if the graph contains a cycle, false otherwise.
 */
bool hasCycle(int numVertices, const WeightedEdgeList& edges)
{
    DisjointSet ds(numVertices);

    for (const auto& [u, v, weight] : edges)
    {
        if (!ds.unionSets(u, v))
        {
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Performs Breadth-First Search (BFS) on an undirected or directed graph.
 *
 * This function visits all nodes in the graph starting from each unvisited node,
 * ensuring that disconnected components are also explored.
 *
 * @param graph The graph represented as an adjacency list.
 *              Each index represents a vertex, and its list contains adjacent vertices.
 * @param visit A function to be called on each visited vertex.
 *
 * @note
 * - The graph is assumed to be represented using 0-based indexing.
 * - The traversal visits each node exactly once.
 *
 * @tparam AdjacencyList A type alias for std::vector<std::list<int>>.
 *
 * @complexity
 * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
 * Space Complexity: O(V), for the visited vector and the BFS queue.
 */
void BFS(const std::vector<std::list<int>>& graph, std::function<bool(int)> visit)
{
    std::vector<bool> visited(graph.size(), false);
    std::queue<int> queue;

    for (size_t start = 0; start < graph.size(); ++start)
    {
        if (!visited[start])
        {
            visited[start] = true;
            queue.push(start);

            while (!queue.empty())
            {
                int current = queue.front();
                queue.pop();

                visited[current] = true;
                if (bool shouldStop = visit(current))
                {
                    return;
                }

                for (int neighbor : graph[current])
                {
                    if (!visited[neighbor])
                    {
                        queue.push(neighbor);
                    }
                }
            }
        }
    }
}

/**
 * @brief Performs Depth-First Search (DFS) on a graph represented as an adjacency list.
 *
 * @param graph The adjacency list representation of the graph.
 * @param visit A callback function to call on each visited node.
 *              If it returns false, the traversal stops early.
 *
 * @timecomplexity O(V + E) where V is the number of vertices and E is the number of edges.
 * @spacecomplexity O(V) for the visited array and stack.
 */
void DFS(const std::vector<std::list<int>>& graph, std::function<bool(int)> visit)
{
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stack;

    for (size_t start = 0; start < graph.size(); ++start)
    {
        if (!visited[start])
        {
            stack.push(start);

            while (!stack.empty())
            {
                int current = stack.top();
                stack.pop();

                if (!visited[current])
                {
                    visited[current] = true;
                    if (bool shouldStop = visit(current))
                    {
                        return;  // Stop traversal if visit returns false
                    }

                    // Push adjacent nodes in reverse to preserve order (optional)
                    for (auto it = graph[current].rbegin(); it != graph[current].rend(); ++it)
                    {
                        if (!visited[*it])
                        {
                            stack.push(*it);
                        }
                    }
                }
            }
        }
    }
}
