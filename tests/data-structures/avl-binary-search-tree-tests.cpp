#include <gtest/gtest.h>
#include <avl-binary-search-tree.hpp>

template <typename T>
std::vector<T> getInOrderValues(AVLNode<T>* root)
{
    std::vector<T> result;
    traverseInOrder(root, [&](AVLNode<T>* node) {
        result.push_back(node->data);
        return false;  // Continue traversal
    });
    return result;
}

TEST(AVLTreeTest, InsertSingleValue)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->height, 0);
}

TEST(AVLTreeTest, LeftLeftRotation)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 30);
    insertAVL(root, 20);
    insertAVL(root, 10);  // Should trigger LL rotation

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->leftChild, nullptr);
    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 30);
}

TEST(AVLTreeTest, RightRightRotation)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 10);
    insertAVL(root, 20);
    insertAVL(root, 30);  // Should trigger RR rotation

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->leftChild, nullptr);
    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 30);
}

TEST(AVLTreeTest, LeftRightRotation)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 30);
    insertAVL(root, 10);
    insertAVL(root, 20);  // Should trigger LR rotation

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->leftChild, nullptr);
    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 30);
}

TEST(AVLTreeTest, RightLeftRotation)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 10);
    insertAVL(root, 30);
    insertAVL(root, 20);  // Should trigger RL rotation

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->leftChild, nullptr);
    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 30);
}

TEST(AVLTreeTest, NoDuplicateInsertions)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 10);
    insertAVL(root, 10);  // Duplicate

    auto traversal = getInOrderValues<int>(root);

    EXPECT_EQ(traversal.size(), 1);  // Should not allow duplicates
    EXPECT_EQ(traversal[0], 10);
}

TEST(AVLTreeTest, InsertMultipleValuesBalancedTree)
{
    AVLNode<int>* root = nullptr;
    std::vector<int> values = {50, 20, 70, 10, 30, 60, 80};

    for (int v : values)
    {
        insertAVL(root, v);
    }

    auto traversal = getInOrderValues<int>(root);

    EXPECT_EQ(traversal, (std::vector<int>{10, 20, 30, 50, 60, 70, 80}));
    EXPECT_LE(abs(getBalanceFactor(root)), 1);
}

TEST(AVLTreeTest, DeepLeftRightRotationChain)
{
    AVLNode<int>* root = nullptr;
    std::vector<int> values = {50, 30, 70, 20, 40, 35};  // Causes LR at node 30

    for (int v : values)
    {
        insertAVL(root, v);
    }

    auto traversal = getInOrderValues<int>(root);

    EXPECT_EQ(traversal, (std::vector<int>{20, 30, 35, 40, 50, 70}));
    EXPECT_LE(abs(getBalanceFactor(root)), 1);
}

TEST(AVLTreeTest, DeepRightLeftRotationChain)
{
    AVLNode<int>* root = nullptr;
    std::vector<int> values = {10, 5, 20, 15, 25, 17};  // Causes RL at node 20

    for (int v : values)
    {
        insertAVL(root, v);
    }

    auto traversal = getInOrderValues<int>(root);

    EXPECT_EQ(traversal, (std::vector<int>{5, 10, 15, 17, 20, 25}));
    EXPECT_LE(abs(getBalanceFactor(root)), 1);
}

TEST(AVLTreeTest, InterleavedInsertions)
{
    AVLNode<int>* root = nullptr;
    std::vector<int> values = {40, 10, 50, 5, 45, 60, 30, 35};

    for (int v : values)
    {
        insertAVL(root, v);
    }

    auto traversal = getInOrderValues<int>(root);
    EXPECT_EQ(traversal, (std::vector<int>{5, 10, 30, 35, 40, 45, 50, 60}));
    EXPECT_LE(abs(getBalanceFactor(root)), 1);
}

TEST(AVLTreeTest, InsertOnlyOneValue)
{
    AVLNode<int>* root = nullptr;
    insertAVL(root, 99);

    auto traversal = getInOrderValues<int>(root);
    EXPECT_EQ(traversal, std::vector<int>{99});
    EXPECT_EQ(root->height, 0);
}

TEST(AVLTreeTest, InsertWithValueGaps)
{
    AVLNode<int>* root = nullptr;
    std::vector<int> values = {100, 500, 300, 200, 400};

    for (int v : values)
    {
        insertAVL(root, v);
    }

    auto traversal = getInOrderValues<int>(root);
    EXPECT_EQ(traversal, (std::vector<int>{100, 200, 300, 400, 500}));
}

TEST(AVLTreeTest, TreeStructureAfterInsertions)
{
    AVLNode<int>* root = nullptr;
    std::vector<int> values = {20, 10, 30, 5, 15, 25, 35};

    for (int v : values)
    {
        insertAVL(root, v);
    }

    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 30);
    EXPECT_EQ(root->leftChild->leftChild->data, 5);
    EXPECT_EQ(root->leftChild->rightChild->data, 15);
    EXPECT_EQ(root->rightChild->leftChild->data, 25);
    EXPECT_EQ(root->rightChild->rightChild->data, 35);
}
