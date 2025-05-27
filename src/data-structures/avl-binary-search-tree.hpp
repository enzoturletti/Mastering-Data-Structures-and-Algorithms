#pragma once

#include <binary-search-tree.hpp>

template <typename T>
struct AVLNode
{
    T data;                           ///< The data stored in the node.
    AVLNode<T>* leftChild{nullptr};   ///< Pointer to the left child node.
    AVLNode<T>* rightChild{nullptr};  ///< Pointer to the right child node.

    /**
     * @brief Constructs a AVLNode with the given value.
     *
     * Initializes the node with the specified value and sets both child pointers to nullptr.
     *
     * @param value The value to store in the node.
     *
     * @complexity Time: O(1), Space: O(1)
     */
    explicit AVLNode(T value) : data(value)
    {
    }

    /**
     * @brief Virtual destructor.
     *
     * Recursively deletes the left and right child nodes to avoid memory leaks.
     */
    virtual ~AVLNode()
    {
        delete leftChild;
        delete rightChild;
    }

    int height{0};
};

/**
 * @brief Recomputes and updates the height of the given AVL node.
 *
 * This function calculates the height of a node based on the cached heights
 * of its left and right children and updates the node's height field.
 * This is used after AVL rotations or insertions to maintain correct heights.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param node Pointer to the node whose height needs to be updated.
 */
template <typename NodeType>
void computeHeight(NodeType* node)
{
    if (!node)
        return;
    int leftHeight = node->leftChild ? node->leftChild->height : -1;
    int rightHeight = node->rightChild ? node->rightChild->height : -1;
    node->height = 1 + std::max(leftHeight, rightHeight);
}

/**
 * @brief Performs a Left-Left (LL) rotation on the given node to restore AVL balance.
 *
 * This rotation is triggered when the left subtree of the left child is taller,
 * resulting in an imbalance factor of +2. It promotes the left child as the new root.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param node Reference to the node where the rotation is applied. It is updated to point to the new subtree root.
 */
template <typename NodeType>
void LLRotation(NodeType*& node)
{
    auto* newRoot = node->leftChild;
    auto* backupValue = newRoot->rightChild;

    // Rotation
    newRoot->rightChild = node;
    node->leftChild = backupValue;

    // Update heights
    computeHeight(node);
    computeHeight(newRoot);

    node = newRoot;
}

/**
 * @brief Performs a Right-Right (RR) rotation on the given node to restore AVL balance.
 *
 * This rotation is used when the right subtree of the right child is taller,
 * causing an imbalance factor of -2. The right child becomes the new root.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param node Reference to the node where the rotation is applied. It is updated to point to the new subtree root.
 */
template <typename NodeType>
void RRRotation(NodeType*& node)
{
    auto* newRoot = node->rightChild;
    auto* backupValue = newRoot->leftChild;

    // Rotation
    newRoot->leftChild = node;
    node->rightChild = backupValue;

    // Update heights
    computeHeight(node);
    computeHeight(newRoot);

    node = newRoot;
}

/**
 * @brief Performs a Left-Right (LR) rotation to restore AVL balance.
 *
 * This is a double rotation triggered when a node's left child has a right-heavy subtree,
 * resulting in a balance factor of +2 with a left child balance factor of -1.
 * It first performs an RR rotation on the left child, then an LL rotation on the node.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param node Reference to the node where the rotation is applied. It is updated to point to the new subtree root.
 */
template <typename NodeType>
void LRRotation(NodeType*& node)
{
    auto* leftChild = node->leftChild;
    auto* newRoot = leftChild->rightChild;

    // Perform the right-left rotation
    leftChild->rightChild = newRoot->leftChild;
    node->leftChild = newRoot->rightChild;

    newRoot->rightChild = node;
    newRoot->leftChild = leftChild;

    // Update the heights
    computeHeight(node);
    computeHeight(newRoot);
    computeHeight(leftChild);

    // Update the root reference
    node = newRoot;
}

/**
 * @brief Performs a Right-Left (RL) rotation to restore AVL balance.
 *
 * This is a double rotation triggered when a node's right child has a left-heavy subtree,
 * resulting in a balance factor of -2 with a right child balance factor of +1.
 * It first performs an LL rotation on the right child, then an RR rotation on the node.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @param node Reference to the node where the rotation is applied. It is updated to point to the new subtree root.
 */
template <typename NodeType>
void RLRotation(NodeType*& node)
{
    auto* rightChild = node->rightChild;
    auto* newRoot = rightChild->leftChild;

    // Perform the right-left rotation
    rightChild->leftChild = newRoot->rightChild;
    node->rightChild = newRoot->leftChild;

    newRoot->leftChild = node;
    newRoot->rightChild = rightChild;

    // Update the heights
    computeHeight(node);
    computeHeight(newRoot);
    computeHeight(rightChild);

    // Update the root reference
    node = newRoot;
}

/**
 * @brief Inserts a value into an AVL tree and performs rebalancing if necessary.
 *
 * This function works like a standard BST insert but ensures the AVL tree remains
 * balanced after each insertion by applying LL, RR, LR, or RL rotations.
 *
 * Duplicate values are ignored.
 *
 * Time Complexity: O(log n) on average and worst-case
 * Space Complexity: O(log n) for recursive call stack
 *
 * @param node Reference to the root node of the AVL tree (or subtree). It may be updated after rotation.
 * @param value The value to insert into the tree.
 */
template <typename NodeType, typename T>
void insertAVL(NodeType*& node, const T value)
{
    if (node == nullptr)
    {
        node = new NodeType(value);
        return;
    }

    insertBST<NodeType>(node, value);

    node->height = getHeight(node);

    int balance = getBalanceFactor(node);
    if (balance == 2)
    {
        int leftBalance = getBalanceFactor(node->leftChild);
        if (leftBalance == 1)
        {
            LLRotation(node);
        }
        else if (leftBalance == -1)
        {
            LRRotation(node);
        }
    }
    else if (balance == -2)
    {
        int rightBalance = getBalanceFactor(node->rightChild);
        if (rightBalance == -1)
        {
            RRRotation(node);
        }
        else if (rightBalance == 1)
        {
            RLRotation(node);
        }
    }
}