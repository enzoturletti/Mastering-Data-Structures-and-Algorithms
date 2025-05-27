#include <gtest/gtest.h>
#include <binary-search-tree.hpp>
#include <vector>

class BinarySearchTreeTest : public ::testing::Test
{
protected:
    BTNode<int>* root = nullptr;

    void TearDown() override
    {
        delete root;
        root = nullptr;
    }

    void insertValues(const std::vector<int>& values)
    {
        for (int value : values)
        {
            insertBST(root, value);
        }
    }
};

TEST_F(BinarySearchTreeTest, InsertBST_EmptyTree)
{
    insertBST(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 10);
}

TEST_F(BinarySearchTreeTest, InsertBST_LeftAndRightChildren)
{
    insertBST(root, 10);
    insertBST(root, 5);
    insertBST(root, 15);

    ASSERT_NE(root->leftChild, nullptr);
    EXPECT_EQ(root->leftChild->data, 5);
    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->rightChild->data, 15);
}

TEST_F(BinarySearchTreeTest, InsertBST_DuplicateValueIgnored)
{
    insertBST(root, 10);
    insertBST(root, 10);  // Duplicate
    EXPECT_EQ(getCount(root), 1);
}

TEST_F(BinarySearchTreeTest, InsertBST_MultipleLevels)
{
    std::vector<int> values = {20, 10, 30, 5, 15, 25, 35};

    for (int val : values)
    {
        insertBST(root, val);
    }

    // Check root node
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 20);

    // Check left and right subtrees
    ASSERT_NE(root->leftChild, nullptr);
    EXPECT_EQ(root->leftChild->data, 10);

    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->rightChild->data, 30);

    // Deeper levels
    EXPECT_EQ(root->leftChild->leftChild->data, 5);
    EXPECT_EQ(root->leftChild->rightChild->data, 15);
    EXPECT_EQ(root->rightChild->leftChild->data, 25);
    EXPECT_EQ(root->rightChild->rightChild->data, 35);

    // Tree size and height
    EXPECT_EQ(getCount(root), 7);
    EXPECT_EQ(getHeight(root), 2);
}

TEST_F(BinarySearchTreeTest, BST_InOrderIsSorted)
{
    std::vector<int> values = {20, 10, 30, 5, 15, 25, 35};
    for (int val : values)
    {
        insertBST(root, val);
    }

    std::vector<int> result;
    traverseInOrder(root, [&](BTNode<int>* node) {
        result.push_back(node->data);
        return false;
    });

    std::vector<int> sorted = values;
    std::sort(sorted.begin(), sorted.end());
    EXPECT_EQ(result, sorted);
}

TEST_F(BinarySearchTreeTest, InOrderTraversal_BST_SortedOrder_WithDuplicatesIgnored)
{
    std::vector<int> input = {10, 5, 15, 10, 5};  // 10 and 5 repeated
    for (int val : input)
    {
        insertBST(root, val);
    }

    std::vector<int> result;
    traverseInOrder(root, [&](BTNode<int>* node) {
        result.push_back(node->data);
        return false;
    });

    // Duplicates should not be inserted
    EXPECT_EQ(result, std::vector<int>({5, 10, 15}));
}

TEST_F(BinarySearchTreeTest, SearchBST_ReturnsCorrectNode_WhenValueExists)
{
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values)
    {
        insertBST(root, val);
    }

    BTNode<int>* result = searchBST(root, 60);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->data, 60);

    result = searchBST(root, 30);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->data, 30);
}

TEST_F(BinarySearchTreeTest, SearchBST_ReturnsNullptr_WhenValueNotInTree)
{
    std::vector<int> values = {15, 10, 20};
    for (int val : values)
    {
        insertBST(root, val);
    }

    BTNode<int>* result = searchBST(root, 5);
    EXPECT_EQ(result, nullptr);

    result = searchBST(root, 25);
    EXPECT_EQ(result, nullptr);
}

TEST_F(BinarySearchTreeTest, SearchBST_ReturnsNullptr_WhenTreeIsEmpty)
{
    BTNode<int>* result = searchBST(root, 42);
    EXPECT_EQ(result, nullptr);
}

TEST_F(BinarySearchTreeTest, SearchBST_FindsRootNode)
{
    insertBST(root, 100);
    BTNode<int>* result = searchBST(root, 100);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->data, 100);
}

TEST_F(BinarySearchTreeTest, DeleteBST_LeafNode)
{
    insertBST(root, 20);
    insertBST(root, 10);
    insertBST(root, 30);

    deleteBST(root, 10);  // Leaf node

    EXPECT_EQ(searchBST(root, 10), nullptr);
    EXPECT_NE(searchBST(root, 20), nullptr);
    EXPECT_NE(searchBST(root, 30), nullptr);
}

TEST_F(BinarySearchTreeTest, DeleteBST_NodeWithOneChild)
{
    insertBST(root, 20);
    insertBST(root, 10);
    insertBST(root, 5);  // 10 has one left child

    deleteBST(root, 10);

    EXPECT_EQ(searchBST(root, 10), nullptr);
    EXPECT_NE(searchBST(root, 5), nullptr);
    EXPECT_NE(searchBST(root, 20), nullptr);
}

TEST_F(BinarySearchTreeTest, DeleteBST_NodeWithTwoChildren)
{
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int val : values)
        insertBST(root, val);

    deleteBST(root, 50);  // Node with two children

    EXPECT_EQ(searchBST(root, 50), nullptr);
    for (int val : values)
    {
        if (val != 50)
            EXPECT_NE(searchBST(root, val), nullptr);
    }
}

TEST_F(BinarySearchTreeTest, DeleteBST_RootNode)
{
    insertBST(root, 100);
    insertBST(root, 50);
    insertBST(root, 150);

    deleteBST(root, 100);

    EXPECT_EQ(searchBST(root, 100), nullptr);
    EXPECT_NE(searchBST(root, 50), nullptr);
    EXPECT_NE(searchBST(root, 150), nullptr);
}

TEST_F(BinarySearchTreeTest, DeleteBST_NonexistentValue)
{
    insertBST(root, 10);
    insertBST(root, 5);
    insertBST(root, 15);

    deleteBST(root, 42);  // Value not in tree

    // Tree should remain unchanged
    EXPECT_NE(searchBST(root, 10), nullptr);
    EXPECT_NE(searchBST(root, 5), nullptr);
    EXPECT_NE(searchBST(root, 15), nullptr);
}

TEST_F(BinarySearchTreeTest, DeleteBST_AllNodes)
{
    std::vector<int> values = {10, 5, 15, 3, 7, 12, 18};
    for (int val : values)
        insertBST(root, val);

    for (int val : values)
        deleteBST(root, val);

    for (int val : values)
        EXPECT_EQ(searchBST(root, val), nullptr);

    EXPECT_EQ(root, nullptr);
}
