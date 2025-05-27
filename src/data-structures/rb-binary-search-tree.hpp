#pragma once

#include <avl-binary-search-tree.hpp>
#include <cassert>
#include <functional>
#include <iostream>
#include <set>

enum class Color
{
    BLACK,
    RED,
};

template <typename T>
struct RBNode
{
    T data;                          ///< The data stored in the node.
    RBNode<T>* leftChild{nullptr};   ///< Pointer to the left child node.
    RBNode<T>* rightChild{nullptr};  ///< Pointer to the right child node.
    RBNode<T>* parent{nullptr};      ///< Pointer to the parent node.

    /**
     * @brief Constructs a RBNode with the given value.
     *
     * Initializes the node with the specified value and sets both child pointers to nullptr.
     *
     * @param value The value to store in the node.
     *
     * @complexity Time: O(1), Space: O(1)
     */
    explicit RBNode(T value) : data(value)
    {
    }

    /**
     * @brief Virtual destructor.
     *
     * Recursively deletes the left and right child nodes to avoid memory leaks.
     */
    virtual ~RBNode()
    {
        std::cout << "Destructing node " << data << std::endl;
        delete leftChild;
        delete rightChild;
    }

    int height{0};
    Color color{Color::BLACK};
};

/**
 * @brief Get the parent of a given node.
 *
 * @param node The node whose parent is to be retrieved.
 * @return Pointer to the parent node, or nullptr if node or parent is null.
 *
 * @complexity Time: O(1), Space: O(1)
 */
template <typename T>
RBNode<T>* getParent(RBNode<T>* node)
{
    if (node && node->parent)
        return node->parent;
    return nullptr;
}

/**
 * @brief Get the grandparent of a given node.
 *
 * @param node The node whose grandparent is to be retrieved.
 * @return Pointer to the grandparent node, or nullptr if not applicable.
 *
 * @complexity Time: O(1), Space: O(1)
 */
template <typename T>
RBNode<T>* getGrandParent(RBNode<T>* node)
{
    if (node && node->parent)
        return node->parent->parent;
    return nullptr;
}

/**
 * @brief Get the uncle of a given node (i.e., parent's sibling).
 *
 * @param node The node whose uncle is to be retrieved.
 * @return Pointer to the uncle node, or nullptr if not applicable.
 *
 * @complexity Time: O(1), Space: O(1)
 */
template <typename T>
RBNode<T>* getUncle(RBNode<T>* node)
{
    RBNode<T>* grandParent = getGrandParent(node);
    if (!grandParent)
        return nullptr;

    if (grandParent->leftChild == node->parent)
        return grandParent->rightChild;
    else
        return grandParent->leftChild;
}

/**
 * @brief Performs a Left-Left (LL) rotation to restore RB tree balance.
 *
 * @param node Reference to the node where rotation is applied.
 *
 * @complexity Time: O(1), Space: O(1)
 */
template <typename T>
void LLRotation(RBNode<T>*& node)
{
    auto* newRoot = node->leftChild;
    auto* backupValue = newRoot->rightChild;
    auto* oldParent = node->parent;

    // Perform rotation
    newRoot->rightChild = node;
    node->leftChild = backupValue;

    // Update parent pointers
    if (backupValue)
        backupValue->parent = node;

    newRoot->parent = oldParent;
    node->parent = newRoot;

    // If node was not the root of the entire tree, update its parent's child pointer
    if (oldParent)
    {
        if (oldParent->leftChild == node)
            oldParent->leftChild = newRoot;
        else if (oldParent->rightChild == node)
            oldParent->rightChild = newRoot;
    }

    // Update heights
    computeHeight(node);
    computeHeight(newRoot);

    // Update node reference to new subtree root
    node = newRoot;
}

template <typename T>
void RRRotation(RBNode<T>*& node)
{
    auto* newRoot = node->rightChild;
    auto* backupValue = newRoot->leftChild;
    auto* oldParent = node->parent;

    // Rotation
    newRoot->leftChild = node;
    node->rightChild = backupValue;

    // Update parent pointers
    if (backupValue)
        backupValue->parent = node;

    newRoot->parent = oldParent;
    node->parent = newRoot;

    if (oldParent)
    {
        if (oldParent->leftChild == node)
            oldParent->leftChild = newRoot;
        else if (oldParent->rightChild == node)
            oldParent->rightChild = newRoot;
    }

    // Update heights
    computeHeight(node);
    computeHeight(newRoot);

    node = newRoot;
}

template <typename T>
void LRRotation(RBNode<T>*& node)
{
    auto* leftChild = node->leftChild;
    auto* newRoot = leftChild->rightChild;
    auto* oldParent = node->parent;

    // Rotation
    leftChild->rightChild = newRoot->leftChild;
    node->leftChild = newRoot->rightChild;

    newRoot->leftChild = leftChild;
    newRoot->rightChild = node;

    // Update parent pointers
    if (leftChild->rightChild)
        leftChild->rightChild->parent = leftChild;
    if (node->leftChild)
        node->leftChild->parent = node;

    newRoot->parent = oldParent;
    leftChild->parent = newRoot;
    node->parent = newRoot;

    if (oldParent)
    {
        if (oldParent->leftChild == node)
            oldParent->leftChild = newRoot;
        else if (oldParent->rightChild == node)
            oldParent->rightChild = newRoot;
    }

    // Update heights
    computeHeight(leftChild);
    computeHeight(node);
    computeHeight(newRoot);

    node = newRoot;
}

template <typename T>
void RLRotation(RBNode<T>*& node)
{
    auto* rightChild = node->rightChild;
    auto* newRoot = rightChild->leftChild;
    auto* oldParent = node->parent;

    // Rotation
    rightChild->leftChild = newRoot->rightChild;
    node->rightChild = newRoot->leftChild;

    newRoot->rightChild = rightChild;
    newRoot->leftChild = node;

    // Update parent pointers
    if (rightChild->leftChild)
        rightChild->leftChild->parent = rightChild;
    if (node->rightChild)
        node->rightChild->parent = node;

    newRoot->parent = oldParent;
    rightChild->parent = newRoot;
    node->parent = newRoot;

    if (oldParent)
    {
        if (oldParent->leftChild == node)
            oldParent->leftChild = newRoot;
        else if (oldParent->rightChild == node)
            oldParent->rightChild = newRoot;
    }

    // Update heights
    computeHeight(rightChild);
    computeHeight(node);
    computeHeight(newRoot);

    node = newRoot;
}

/**
 * @brief Inserts a value into a Red-Black tree and rebalances it.
 *
 * If the tree is empty, creates the root node. Otherwise, inserts the value
 * using BST rules and restores RB properties via rotations and recoloring.
 *
 * @param root Reference to the root of the tree.
 * @param value The value to insert into the tree.
 *
 * @complexity Average Time: O(log n), Worst Case Time: O(log n)
 * @complexity Space: O(log n) due to recursive balancing stack
 */
template <typename T>
void insertRB(RBNode<T>*& root, const T value)
{
    if (root == nullptr)
    {
        root = new RBNode<T>(value);
        root->color = Color::BLACK;
        return;
    }

    auto newNode = new RBNode<T>(value);
    newNode->color = Color::RED;

    RBNode<T>* current = root;
    RBNode<T>* parent = nullptr;

    // Find where to insert the new node
    while (current != nullptr)
    {
        parent = current;
        if (value < current->data)
        {
            current = current->leftChild;
        }
        else if (value > current->data)
        {
            current = current->rightChild;
        }
        else
        {
            delete newNode;
        }
    }

    // Update new node parent
    newNode->parent = parent;

    // Update new node color
    newNode->color = Color::RED;

    // Link parent to newNode.
    if (value < parent->data)
    {
        parent->leftChild = newNode;
    }
    else
    {
        parent->rightChild = newNode;
    }

    std::function<void(RBNode<T>*&)> balance_node_function = [&balance_node_function, &root, &value](RBNode<T>*& node) {
        // Original nodes before balance.
        auto* uncleNode = getUncle(node);
        auto* parent = getParent(node);
        auto* grandParent = getGrandParent(node);

        const bool isRoot = (parent == nullptr);
        if (isRoot)
        {
            node->color = Color::BLACK;
            return;
        }

        const bool should_balance = (parent->color == Color::RED);
        if (!should_balance)
        {
            return;
        }

        // Only recoloring strategy
        if (uncleNode && uncleNode->color == Color::RED)
        {
            uncleNode->color = Color::BLACK;
            parent->color = Color::BLACK;
            grandParent->color = Color::RED;

            balance_node_function(grandParent);
        }
        else if (
            parent && grandParent &&
            ((parent == grandParent->rightChild && node == parent->rightChild) ||
             (parent == grandParent->leftChild && node == parent->leftChild)))
        {
            // Update root.
            if (grandParent == root)
            {
                root = parent;
            }

            // Recolor
            parent->color = Color::BLACK;  // New "Root" color.
            grandParent->color = Color::RED;

            // Perform rotation
            if (parent == grandParent->rightChild)
            {
                RRRotation(grandParent);
            }
            else
            {
                LLRotation(grandParent);
            }
        }
        else if (
            parent && grandParent &&
            ((parent == grandParent->leftChild && node == parent->rightChild) ||
             (parent == grandParent->rightChild && node == parent->leftChild)))
        {
            // Update root.
            if (grandParent == root)
            {
                root = node;
            }

            // Recolor
            node->color = Color::BLACK;  // New "root" of the rotated subtree
            parent->color = Color::RED;
            grandParent->color = Color::RED;

            // Perform rotation
            if (parent == grandParent->leftChild)
            {
                LRRotation(grandParent);
            }
            else
            {
                RLRotation(grandParent);
            }
        }
    };

    balance_node_function(newNode);
}
