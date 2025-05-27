#include <gtest/gtest.h>
#include <binary-tree.hpp>
#include <vector>

class BinaryTreeTest : public ::testing::Test
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
            insertLevelOrder(root, value);
        }
    }
};

TEST_F(BinaryTreeTest, InsertSingleNode)
{
    insertLevelOrder(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 10);
}

TEST_F(BinaryTreeTest, InsertMultipleNodes_LevelOrderStructure)
{
    insertValues({10, 20, 30});
    EXPECT_EQ(root->data, 10);
    ASSERT_NE(root->leftChild, nullptr);
    EXPECT_EQ(root->leftChild->data, 20);
    ASSERT_NE(root->rightChild, nullptr);
    EXPECT_EQ(root->rightChild->data, 30);
}

TEST_F(BinaryTreeTest, CountEmptyTree)
{
    EXPECT_EQ(getCount(root), 0);
}

TEST_F(BinaryTreeTest, CountMultipleNodes)
{
    insertValues({1, 2, 3, 4});
    EXPECT_EQ(getCount(root), 4);
}

TEST_F(BinaryTreeTest, HeightEmptyTree)
{
    EXPECT_EQ(getHeight(root), -1);
}

TEST_F(BinaryTreeTest, HeightSingleNode)
{
    insertLevelOrder(root, 1);
    EXPECT_EQ(getHeight(root), 0);
}

TEST_F(BinaryTreeTest, HeightBalancedTree)
{
    insertValues({1, 2, 3, 4, 5, 6, 7});
    EXPECT_EQ(getHeight(root), 2);
}

TEST_F(BinaryTreeTest, HeightUnbalancedTree)
{
    // Manually construct unbalanced tree
    root = new BTNode<int>(1);
    root->leftChild = new BTNode<int>(2);
    root->leftChild->leftChild = new BTNode<int>(3);

    EXPECT_EQ(getHeight(root), 2);

    delete root;

    root = new BTNode<int>(1);
    root->rightChild = new BTNode<int>(2);
    root->rightChild->rightChild = new BTNode<int>(3);

    EXPECT_EQ(getHeight(root), 2);
}

TEST_F(BinaryTreeTest, IsCompleteEmptyTree)
{
    EXPECT_TRUE(isComplete(root));
}

TEST_F(BinaryTreeTest, IsCompleteSingleNode)
{
    insertLevelOrder(root, 1);
    EXPECT_TRUE(isComplete(root));
}

TEST_F(BinaryTreeTest, IsCompleteFullTree)
{
    insertValues({1, 2, 3, 4, 5, 6});
    EXPECT_TRUE(isComplete(root));
}

TEST_F(BinaryTreeTest, IsNotCompleteMissingLeftFirst)
{
    root = new BTNode<int>(1);
    root->rightChild = new BTNode<int>(2);
    EXPECT_FALSE(isComplete(root));
}

TEST_F(BinaryTreeTest, IsNotCompleteLeftMissingLater)
{
    insertValues({1, 2, 3, 4});
    EXPECT_TRUE(isComplete(root));
    root->rightChild = nullptr;  // Force gap
    EXPECT_FALSE(isComplete(root));
}

TEST_F(BinaryTreeTest, LeafCountEmptyTree)
{
    EXPECT_EQ(getLeafNodesCount(root), 0);
}

TEST_F(BinaryTreeTest, LeafCountSingleNode)
{
    insertLevelOrder(root, 1);
    EXPECT_EQ(getLeafNodesCount(root), 1);
}

TEST_F(BinaryTreeTest, LeafCountMultiple)
{
    insertValues({1, 2, 3, 4, 5});
    EXPECT_EQ(getLeafNodesCount(root), 3);  // leaves: 3 4 and 5
}

TEST_F(BinaryTreeTest, InOrderTraversal)
{
    insertValues({1, 2, 3});  // level order: 1, 2, 3

    std::vector<int> result;
    traverseInOrder(root, [&](BTNode<int>* node) {
        result.push_back(node->data);
        return false;
    });

    EXPECT_EQ(result, std::vector<int>({2, 1, 3}));
}

TEST_F(BinaryTreeTest, PreOrderTraversal)
{
    insertValues({1, 2, 3});
    std::vector<int> result;
    traversePreOrder(root, [&](BTNode<int>* node) {
        result.push_back(node->data);
        return false;
    });

    EXPECT_EQ(result, std::vector<int>({1, 2, 3}));
}

TEST_F(BinaryTreeTest, PostOrderTraversal)
{
    insertValues({1, 2, 3});
    std::vector<int> result;
    traversePostOrder(root, [&](BTNode<int>* node) {
        result.push_back(node->data);
        return false;
    });

    EXPECT_EQ(result, std::vector<int>({2, 3, 1}));
}

TEST_F(BinaryTreeTest, DestructorDeletesAll)
{
    auto* root = new BTNode<int>(1);
    insertLevelOrder(root, 2);
    insertLevelOrder(root, 3);
    root->rightChild->rightChild = new BTNode<int>(4);
    delete root;
    SUCCEED();
}

TEST_F(BinaryTreeTest, BalanceFactor_NullTree)
{
    root = nullptr;
    EXPECT_EQ(getBalanceFactor(root), 0);
}

TEST_F(BinaryTreeTest, BalanceFactor_SingleNode)
{
    root = new BTNode<int>(10);
    EXPECT_EQ(getBalanceFactor(root), 0);
}

TEST_F(BinaryTreeTest, BalanceFactor_LeftHeavyTree)
{
    root = new BTNode<int>(1);
    root->leftChild = new BTNode<int>(2);
    root->leftChild->leftChild = new BTNode<int>(3);
    // Tree:
    //     1
    //    /
    //   2
    //  /
    // 3
    EXPECT_EQ(getBalanceFactor(root), 2);
}

TEST_F(BinaryTreeTest, BalanceFactor_RightHeavyTree)
{
    root = new BTNode<int>(1);
    root->rightChild = new BTNode<int>(2);
    root->rightChild->rightChild = new BTNode<int>(3);
    // Tree:
    // 1
    //  \
    //   2
    //    \
    //     3
    EXPECT_EQ(getBalanceFactor(root), -2);
}

TEST_F(BinaryTreeTest, BalanceFactor_LeftRightRotationNeeded)
{
    root = new BTNode<int>(3);
    root->leftChild = new BTNode<int>(1);
    root->leftChild->rightChild = new BTNode<int>(2);
    // Tree:
    //   3
    //  /
    // 1
    //   \
    //    2
    EXPECT_EQ(getBalanceFactor(root), 2);
}

TEST_F(BinaryTreeTest, BalanceFactor_RightLeftRotationNeeded)
{
    root = new BTNode<int>(2);
    root->rightChild = new BTNode<int>(3);
    root->rightChild->leftChild = new BTNode<int>(1);
    // Tree:
    //   2
    //    \
    //     3
    //   /
    //  1
    EXPECT_EQ(getBalanceFactor(root), -2);
}

TEST_F(BinaryTreeTest, BalanceFactor_LeftLeftRotationNeeded)
{
    root = new BTNode<int>(3);
    root->leftChild = new BTNode<int>(2);
    root->leftChild->leftChild = new BTNode<int>(1);
    // Tree:
    //     3
    //    /
    //   2
    //  /
    // 1
    EXPECT_EQ(getBalanceFactor(root), 2);
}

TEST_F(BinaryTreeTest, BalanceFactor_RightRightRotationNeeded)
{
    root = new BTNode<int>(1);
    root->rightChild = new BTNode<int>(2);
    root->rightChild->rightChild = new BTNode<int>(3);
    // Tree:
    // 1
    //  \
    //   2
    //    \
    //     3
    EXPECT_EQ(getBalanceFactor(root), -2);
}

TEST_F(BinaryTreeTest, BalanceFactor_BalancedTree)
{
    root = new BTNode<int>(2);
    root->leftChild = new BTNode<int>(1);
    root->rightChild = new BTNode<int>(3);
    // Tree:
    //   2
    //  / \
    // 1   3
    EXPECT_EQ(getBalanceFactor(root), 0);
}
