#pragma once

#include <binary-tree.hpp>

/**
 * @brief Inserts a value into the binary search tree (BST), maintaining BST ordering.
 *
 * If the tree is empty, a new node is created. If the value is already present,
 * no insertion is performed (no duplicates).
 *
 * @param node The root node (can be null).
 * @param value The value to insert.
 * @complexity Time: O(h), where h is the height of the tree. Space: O(h) due to recursion stack.
 * In a balanced BST (e.g., AVL or Red-Black Tree), operations such as search, insert, and delete are logarithmic.
 * However, in an unbalanced BST (e.g., inserting sorted data without self-balancing), the tree degenerates into a list,
 * resulting in linear time complexity.
 */
template <typename NodeType, typename T>
void insertBST(NodeType*& node, const T value)
{
    if (node == nullptr)
    {
        node = new NodeType(value);
        return;
    }

    if (value < node->data)
    {
        insertBST(node->leftChild, value);
    }
    else if (value > node->data)
    {
        insertBST(node->rightChild, value);
    }
}

/**
 * @brief Deletes a node with the specified value from a Binary Search Tree (BST).
 *
 * This function recursively searches for the node with the given value in the BST rooted at `node`
 * and removes it while preserving the BST property. If the node has two children, the in-order
 * predecessor or successor is used to replace it, depending on the balance factor (typically used in AVL trees).
 *
 * @param node Reference to the pointer to the root of the BST or subtree.
 * @param value The value of the node to be deleted.
 *
 * @note Assumes that `getBalanceFactor`, `getInorderPredecessor`, and `getInorderSuccessor` are defined elsewhere.
 *       If used in a simple BST (not AVL), consider using only left/right child checks instead of balance factor.
 *
 * @complexity
 * Time Complexity: O(h), where h is the height of the tree.
 *   - O(log n) for balanced BSTs (e.g., AVL trees).
 *   - O(n) in the worst case for skewed trees (e.g., linked-list-like).
 *
 * Space Complexity: O(h) due to recursion stack.
 *   - O(log n) in balanced trees.
 *   - O(n) in the worst case for unbalanced trees.
 */

template <typename NodeType, typename T>
void deleteBST(NodeType*& node, const T value)
{
    if (node == nullptr)
    {
        // Base case: node not found
        return;
    }

    // Recursive case: traverse left if value is smaller
    if (value < node->data)
    {
        deleteBST(node->leftChild, value);
    }
    // Traverse right if value is greater
    else if (value > node->data)
    {
        deleteBST(node->rightChild, value);
    }
    else
    {
        // Node found - perform deletion

        // Case 1: Leaf node (no children)
        if (node->leftChild == nullptr && node->rightChild == nullptr)
        {
            delete node;
            node = nullptr;
        }
        // Case 2 & 3: Node has one or two children
        else
        {
            // Determine balance to decide between predecessor and successor
            const int balanceFactor = getBalanceFactor(node);

            if (balanceFactor > 0)
            {
                // Use in-order predecessor (max of left subtree)
                NodeType* inOrderPredecessor = getInorderPredecessor(node);
                node->data = inOrderPredecessor->data;
                deleteBST(node->leftChild, inOrderPredecessor->data);
            }
            else
            {
                // Use in-order successor (min of right subtree)
                NodeType* inOrderSuccessor = getInorderSuccessor(node);
                node->data = inOrderSuccessor->data;
                deleteBST(node->rightChild, inOrderSuccessor->data);
            }
        }
    }
}

/**
 * @brief Searches for a node with the given value in the binary search tree.
 *
 * Performs a binary search based on the BST property:
 * left < node < right.
 *
 * @param node The root of the BST to search.
 * @param value The value to find.
 * @return Pointer to the node if found, nullptr otherwise.
 *
 * @complexity
 * - Time: O(h), where h is the height of the tree.
 *   - Best/Average Case: O(log n) when the tree is balanced (h ≈ log₂(n)).
 *   - Worst Case: O(n) when the tree is completely unbalanced (e.g., all nodes are in a single left/right chain).
 * - Space: O(h) due to recursion stack (same best/worst case bounds).
 *
 * In a balanced BST (e.g., AVL or Red-Black Tree), operations such as search, insert, and delete are logarithmic.
 * However, in an unbalanced BST (e.g., inserting sorted data without self-balancing), the tree degenerates into a list,
 * resulting in linear time complexity.
 */
template <typename NodeType, typename T>
NodeType* searchBST(NodeType* node, const T value)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (value == node->data)
    {
        return node;
    }

    if (value < node->data)
    {
        return searchBST(node->leftChild, value);
    }
    else
    {
        return searchBST(node->rightChild, value);
    }
}
