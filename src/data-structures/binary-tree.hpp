#pragma once

#include <functional>
#include <queue.hpp>

/**
 * @brief A generic node in a binary tree.
 *
 * This structure represents a single node within a binary tree. It stores a value
 * of type T and pointers to its left and right children. It includes a constructor
 * to initialize the data and a virtual destructor that recursively deletes the children.
 */
template <typename T>
struct BTNode
{
    T data;                          ///< The data stored in the node.
    BTNode<T>* leftChild{nullptr};   ///< Pointer to the left child node.
    BTNode<T>* rightChild{nullptr};  ///< Pointer to the right child node.

    /**
     * @brief Constructs a BTNode with the given value.
     *
     * Initializes the node with the specified value and sets both child pointers to nullptr.
     *
     * @param value The value to store in the node.
     *
     * @complexity Time: O(1), Space: O(1)
     */
    explicit BTNode(T value) : data(value)
    {
    }

    /**
     * @brief Virtual destructor.
     *
     * Recursively deletes the left and right child nodes to avoid memory leaks.
     */
    virtual ~BTNode()
    {
        delete leftChild;
        delete rightChild;
    }
};

/**
 * @brief Helper for level-order traversal.
 */
template <typename NodeType, typename Visitor>
void traverseLevelOrder(NodeType* node, Visitor&& visit)
{
    if (node == nullptr)
    {
        return;
    }

    Queue<NodeType*> queue;
    queue.push(node);

    while (!queue.isEmpty())
    {
        NodeType* currentNode = queue.front();
        queue.pop();

        if (visit(currentNode))
        {
            return;
        }

        if (currentNode->leftChild != nullptr)
        {
            queue.push(currentNode->leftChild);
        }

        if (currentNode->rightChild != nullptr)
        {
            queue.push(currentNode->rightChild);
        }
    }
}

/**
 * @brief Helper for pre-order traversal.
 */
template <typename NodeType, typename Visitor>
void traversePreOrder(NodeType* node, Visitor&& visit)
{
    if (node == nullptr)
    {
        return;
    }

    if (visit(node))
    {
        return;
    }

    traversePreOrder(node->leftChild, std::forward<Visitor>(visit));
    traversePreOrder(node->rightChild, std::forward<Visitor>(visit));
}

/**
 * @brief Helper for in-order traversal.
 */
template <typename NodeType, typename Visitor>
void traverseInOrder(NodeType* node, Visitor&& visit)
{
    if (node == nullptr)
    {
        return;
    }

    traverseInOrder(node->leftChild, std::forward<Visitor>(visit));

    if (visit(node))
    {
        return;
    }

    traverseInOrder(node->rightChild, std::forward<Visitor>(visit));
}

/**
 * @brief Helper for post-order traversal.
 */
template <typename NodeType, typename Visitor>
void traversePostOrder(NodeType* node, Visitor&& visit)
{
    if (node == nullptr)
    {
        return;
    }

    traversePostOrder(node->leftChild, std::forward<Visitor>(visit));
    traversePostOrder(node->rightChild, std::forward<Visitor>(visit));

    if (visit(node))
    {
        return;
    }
}

/**
 * @brief Inserts a node with the given value into the binary tree using level-order traversal.
 * @param value The value to insert.
 * @complexity Time: O(n), where n is the number of nodes (level-order traversal). Space: O(n) due to queue.
 */
template <typename NodeType, typename T>
void insertLevelOrder(NodeType*& node, const T value)
{
    NodeType* newNode = new NodeType(value);

    if (node == nullptr)
    {
        node = newNode;
        return;
    }

    traverseLevelOrder<NodeType>(node, [&](NodeType* currentNode) {
        if (currentNode->leftChild == nullptr)
        {
            currentNode->leftChild = newNode;
            return true;
        }

        if (currentNode->rightChild == nullptr)
        {
            currentNode->rightChild = newNode;
            return true;
        }

        return false;
    });
}

/**
 * @brief Checks whether the binary tree is complete.
 *
 * A binary tree is complete if all levels are fully filled except possibly the last,
 * and all nodes in the last level appear as far left as possible.
 *
 * @return true if the binary tree is complete, false otherwise.
 * @complexity Time: O(n), where n is the number of nodes. Space: O(n), due to internal queue.
 */
template <typename NodeType>
[[nodiscard]] bool isComplete(NodeType* node)
{
    bool nullFound = false;
    bool result = true;

    traverseLevelOrder<NodeType>(node, [&nullFound, &result](NodeType* currentNode) {
        // Left child check
        if (currentNode->leftChild)
        {
            if (nullFound)  // non-null left after null → not complete
            {
                result = false;
                return true;  // stop traversal
            }
        }
        else
        {
            nullFound = true;  // mark that a null was seen
        }

        // Right child check
        if (currentNode->rightChild)
        {
            if (nullFound)  // non-null right after null → not complete
            {
                result = false;
                return true;
            }
        }
        else
        {
            nullFound = true;
        }

        return false;  // continue traversal
    });

    return result;
}

/**
 * @brief Counts the number of nodes in the tree that hold a non-nullopt value.
 *
 * @return The number of non-null nodes in the tree.
 * @complexity Time: O(n), where n is the number of nodes. Space: O(h), where h is the tree height (recursion
 * stack).
 */
template <typename NodeType>
[[nodiscard]] size_t getCount(NodeType* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return 1 + getCount(node->leftChild) + getCount(node->rightChild);
}

/**
 * @brief Calculates the height of the binary tree.
 * The number of nodes from the deepest leaf node to the node node.
 *
 * This function performs a depth-first traversal to calculate the height recursively.
 *
 * @return The height of the tree. If the tree is empty or all nodes are nullprt, the height is -1.
 * @complexity Time: O(n), where n is the number of nodes in the tree. Space: O(h), where h is the tree height (due
 * to recursion stack).
 */
template <typename NodeType>
[[nodiscard]] int getHeight(NodeType* node)
{
    if (node == nullptr)
    {
        return -1;
    }

    int leftHeight = getHeight(node->leftChild);
    int rightHeight = getHeight(node->rightChild);
    return 1 + std::max(leftHeight, rightHeight);
}

/**
 * @brief Calculates the balance factor of a binary tree node.
 *
 * The balance factor is defined as the height difference between the left and right subtrees
 * of a node: balance = height(left subtree) - height(right subtree).
 *
 * A balance factor of:
 *   -  0 means the node is perfectly balanced,
 *   - >0 means the left subtree is taller,
 *   - <0 means the right subtree is taller.
 *
 * @param node Pointer to the binary tree node.
 * @return The balance factor of the node. Returns 0 if the node is null.
 *
 * @complexity Time: O(n), where n is the number of nodes in the subtree rooted at `node`.
 * Space: O(h), where h is the height of the subtree (due to recursion stack).
 */
template <typename NodeType>
[[nodiscard]] int getBalanceFactor(NodeType* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

template <typename NodeType>
[[nodiscard]] size_t getLeafNodesCount(NodeType* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    const bool noLeftChildrens = (node->leftChild == nullptr);
    const bool noRightChildrens = (node->rightChild == nullptr);

    if (noLeftChildrens && noRightChildrens)
    {
        return 1;
    }

    return getLeafNodesCount(node->leftChild) + getLeafNodesCount(node->rightChild);
}

/**
 * @brief Finds the inorder predecessor of the given node in a BST/AVL.
 *
 * The inorder predecessor is the node with the largest value
 * smaller than the current node's value.
 *
 * Assumes the node has a left subtree.
 *
 * Time Complexity: O(h), where h is the height of the subtree.
 *
 * @param node Pointer to the node whose predecessor is needed.
 * @return Pointer to the inorder predecessor, or nullptr if none exists.
 */
template <typename NodeType>
[[nodiscard]] NodeType* getInorderPredecessor(NodeType* node)
{
    if (!node || !node->leftChild)
        return nullptr;

    NodeType* current = node->leftChild;
    // The rightmost node in left subtree is the predecessor
    while (current->rightChild != nullptr)
    {
        current = current->rightChild;
    }
    return current;
}

/**
 * @brief Finds the inorder successor of the given node in a BST/AVL.
 *
 * The inorder successor is the node with the smallest value
 * greater than the current node's value.
 *
 * Assumes the node has a right subtree.
 *
 * Time Complexity: O(h), where h is the height of the subtree.
 *
 * @param node Pointer to the node whose successor is needed.
 * @return Pointer to the inorder successor, or nullptr if none exists.
 */
template <typename NodeType>
[[nodiscard]] NodeType* getInorderSuccessor(NodeType* node)
{
    if (!node || !node->rightChild)
        return nullptr;

    NodeType* current = node->rightChild;
    // The leftmost node in right subtree is the successor
    while (current->leftChild != nullptr)
    {
        current = current->leftChild;
    }
    return current;
}
