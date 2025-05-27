#include <gtest/gtest.h>
#include <chrono>
#include <random>
#include <rb-binary-search-tree.hpp>
#include <set>

// Helper function to validate red-black tree properties
template <typename T>
bool isRedBlackTreeValid(RBNode<T>* root, int& blackHeight, bool isRoot = true)
{
    if (!root)
    {
        blackHeight = 1;
        return true;
    }

    // Property 1: Node color must be RED or BLACK
    if (root->color != Color::RED && root->color != Color::BLACK)
    {
        std::cout << "Node " << root->data << " has invalid color!" << std::endl;
        return false;
    }

    // Property 2: Root must be black
    if (isRoot && root->color != Color::BLACK)
    {
        std::cout << "Root node " << root->data << " is not black!" << std::endl;
        return false;
    }

    // Property 3: Red node cannot have red children
    if (root->color == Color::RED)
    {
        if (root->leftChild && root->leftChild->color == Color::RED)
        {
            std::cout << "Red violation: Node " << root->data << " and left child " << root->leftChild->data
                      << " are both RED." << std::endl;
            return false;
        }
        if (root->rightChild && root->rightChild->color == Color::RED)
        {
            std::cout << "Red violation: Node " << root->data << " and right child " << root->rightChild->data
                      << " are both RED." << std::endl;
            return false;
        }
    }

    int leftBlackHeight = 0;
    int rightBlackHeight = 0;

    if (!isRedBlackTreeValid(root->leftChild, leftBlackHeight, false))
    {
        std::cout << "Left subtree of node " << root->data << " is invalid!" << std::endl;
        return false;
    }

    if (!isRedBlackTreeValid(root->rightChild, rightBlackHeight, false))
    {
        std::cout << "Right subtree of node " << root->data << " is invalid!" << std::endl;
        return false;
    }

    // Property 4: All paths must have same number of black nodes
    if (leftBlackHeight != rightBlackHeight)
    {
        std::cout << "Black height mismatch at node " << root->data << ": left = " << leftBlackHeight
                  << ", right = " << rightBlackHeight << std::endl;
        return false;
    }

    blackHeight = leftBlackHeight + (root->color == Color::BLACK ? 1 : 0);

    return true;
}

template <typename T>
bool isRedBlackTreeValid(RBNode<T>* root)
{
    int blackHeight = 0;
    return isRedBlackTreeValid(root, blackHeight);
}

template <typename T>
class RedBlackBinarySearchTreeTest : public ::testing::Test
{
protected:
    RBNode<T>* root = nullptr;

    void TearDown() override
    {
        delete root;
        root = nullptr;
    }
};

// Explicit instantiation for int type
using RBTreeTestInt = RedBlackBinarySearchTreeTest<int>;

TEST_F(RBTreeTestInt, InsertSingleNode_ShouldBeBlackRoot)
{
    insertRB(root, 10);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->color, Color::BLACK);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_TRUE(isRedBlackTreeValid(root));
}

TEST_F(RBTreeTestInt, InsertTwoNodes_ShouldBalanceCorrectly)
{
    insertRB(root, 10);
    insertRB(root, 5);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->leftChild->data, 5);
    EXPECT_EQ(root->leftChild->color, Color::RED);
    EXPECT_TRUE(isRedBlackTreeValid(root));
}

TEST_F(RBTreeTestInt, LargeInsertion_ShouldMaintainRBProperties_1)
{
    for (int val : {10, 20, 30, 15, 25, 5, 1, 6, 7, 17})
    {
        insertRB(root, val);
    }
    EXPECT_TRUE(isRedBlackTreeValid(root));
}

TEST_F(RBTreeTestInt, LargeInsertion_ShouldMaintainRBProperties_2)
{
    // Insertion Nº 1:
    root = new RBNode(7);
    auto* node_7 = root;

    EXPECT_EQ(root->data, 7);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);

    // Insertion Nº 2:
    insertRB(root, 45);
    auto* node_45 = searchBST(root, 45);

    EXPECT_EQ(node_7->data, 7);
    EXPECT_EQ(node_7->parent, nullptr);
    EXPECT_EQ(node_7->color, Color::BLACK);
    EXPECT_EQ(node_7->rightChild, node_45);
    EXPECT_EQ(node_7->leftChild, nullptr);

    // Insertion Nº 3:
    insertRB(root, 10);
    auto* node_10 = searchBST(root, 10);
    EXPECT_EQ(root->data, node_10->data);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, nullptr);
    EXPECT_EQ(node_10->color, Color::BLACK);
    EXPECT_EQ(node_10->rightChild, node_45);
    EXPECT_EQ(node_10->leftChild, node_7);

    EXPECT_EQ(node_7->data, 7);
    EXPECT_EQ(node_7->parent, node_10);
    EXPECT_EQ(node_7->color, Color::RED);
    EXPECT_EQ(node_7->rightChild, nullptr);
    EXPECT_EQ(node_7->leftChild, nullptr);

    EXPECT_EQ(node_45->data, 45);
    EXPECT_EQ(node_45->parent, node_10);
    EXPECT_EQ(node_45->color, Color::RED);
    EXPECT_EQ(node_45->rightChild, nullptr);
    EXPECT_EQ(node_45->leftChild, nullptr);

    // Insertion Nº 4:
    insertRB(root, 58);
    auto* node_58 = searchBST(root, 58);
    EXPECT_EQ(root->data, node_10->data);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, nullptr);
    EXPECT_EQ(node_10->color, Color::BLACK);
    EXPECT_EQ(node_10->rightChild, node_45);
    EXPECT_EQ(node_10->leftChild, node_7);

    EXPECT_EQ(node_7->data, 7);
    EXPECT_EQ(node_7->parent, node_10);
    EXPECT_EQ(node_7->color, Color::BLACK);
    EXPECT_EQ(node_7->rightChild, nullptr);
    EXPECT_EQ(node_7->leftChild, nullptr);

    EXPECT_EQ(node_45->data, 45);
    EXPECT_EQ(node_45->parent, node_10);
    EXPECT_EQ(node_45->color, Color::BLACK);
    EXPECT_EQ(node_45->rightChild, node_58);
    EXPECT_EQ(node_45->leftChild, nullptr);

    EXPECT_EQ(node_58->data, 58);
    EXPECT_EQ(node_58->parent, node_45);
    EXPECT_EQ(node_58->color, Color::RED);
    EXPECT_EQ(node_58->rightChild, nullptr);
    EXPECT_EQ(node_58->leftChild, nullptr);

    // Insertion Nº 5:
    insertRB(root, 49);
    auto* node_49 = searchBST(root, 49);
    EXPECT_EQ(root->data, node_10->data);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, nullptr);
    EXPECT_EQ(node_10->color, Color::BLACK);
    EXPECT_EQ(node_10->rightChild, node_49);
    EXPECT_EQ(node_10->leftChild, node_7);

    EXPECT_EQ(node_7->data, 7);
    EXPECT_EQ(node_7->parent, node_10);
    EXPECT_EQ(node_7->color, Color::BLACK);
    EXPECT_EQ(node_7->rightChild, nullptr);
    EXPECT_EQ(node_7->leftChild, nullptr);

    EXPECT_EQ(node_45->data, 45);
    EXPECT_EQ(node_45->parent, node_49);
    EXPECT_EQ(node_45->color, Color::RED);
    EXPECT_EQ(node_45->rightChild, nullptr);
    EXPECT_EQ(node_45->leftChild, nullptr);

    EXPECT_EQ(node_58->data, 58);
    EXPECT_EQ(node_58->parent, node_49);
    EXPECT_EQ(node_58->color, Color::RED);
    EXPECT_EQ(node_58->rightChild, nullptr);
    EXPECT_EQ(node_58->leftChild, nullptr);

    EXPECT_EQ(node_49->data, 49);
    EXPECT_EQ(node_49->parent, node_10);
    EXPECT_EQ(node_49->color, Color::BLACK);
    EXPECT_EQ(node_49->rightChild, node_58);
    EXPECT_EQ(node_49->leftChild, node_45);

    // Insertion Nº 6:
    insertRB(root, 40);
    auto* node_40 = searchBST(root, 40);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, nullptr);
    EXPECT_EQ(node_10->color, Color::BLACK);
    EXPECT_EQ(node_10->rightChild, node_49);
    EXPECT_EQ(node_10->leftChild, node_7);

    EXPECT_EQ(node_7->data, 7);
    EXPECT_EQ(node_7->parent, node_10);
    EXPECT_EQ(node_7->color, Color::BLACK);
    EXPECT_EQ(node_7->rightChild, nullptr);
    EXPECT_EQ(node_7->leftChild, nullptr);

    EXPECT_EQ(node_45->data, 45);
    EXPECT_EQ(node_45->parent, node_49);
    EXPECT_EQ(node_45->color, Color::BLACK);
    EXPECT_EQ(node_45->rightChild, nullptr);
    EXPECT_EQ(node_45->leftChild, node_40);

    EXPECT_EQ(node_58->data, 58);
    EXPECT_EQ(node_58->parent, node_49);
    EXPECT_EQ(node_58->color, Color::BLACK);
    EXPECT_EQ(node_58->rightChild, nullptr);
    EXPECT_EQ(node_58->leftChild, nullptr);

    EXPECT_EQ(node_49->data, 49);
    EXPECT_EQ(node_49->parent, node_10);
    EXPECT_EQ(node_49->color, Color::RED);
    EXPECT_EQ(node_49->rightChild, node_58);
    EXPECT_EQ(node_49->leftChild, node_45);

    EXPECT_EQ(node_40->data, 40);
    EXPECT_EQ(node_40->parent, node_45);
    EXPECT_EQ(node_40->color, Color::RED);
    EXPECT_EQ(node_40->rightChild, nullptr);
    EXPECT_EQ(node_40->leftChild, nullptr);

    EXPECT_TRUE(isRedBlackTreeValid(root));
}

TEST_F(RBTreeTestInt, LargeInsertion_ShouldMaintainRBProperties_3)
{
    for (int val : {67, 71, 21, 44, 36, 12, 24, 33, 29, 9, 4, 27, 92, 18, 47, 64})
    {
        insertRB(root, val);
    }
    EXPECT_TRUE(isRedBlackTreeValid(root));
}

TEST_F(RBTreeTestInt, LargeInsertion_ShouldMaintainRBProperties_4)
{
    for (int val : {1, 99, 10, 14, 95, 35, 58, 54, 59, 67})
    {
        // insertRB(root, val);
    }
    // EXPECT_TRUE(isRedBlackTreeValid(root));

    auto* root = new RBNode(1);
    EXPECT_EQ(root->data, 1);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);

    auto* node_1 = searchBST(root, 1);

    // Inserts
    insertRB(root, 99);
    insertRB(root, 10);
    insertRB(root, 14);
    insertRB(root, 95);
    insertRB(root, 35);
    insertRB(root, 58);
    insertRB(root, 54);

    auto* node_99 = searchBST(root, 99);
    auto* node_10 = searchBST(root, 10);
    auto* node_14 = searchBST(root, 14);
    auto* node_95 = searchBST(root, 95);
    auto* node_35 = searchBST(root, 35);
    auto* node_58 = searchBST(root, 58);
    auto* node_54 = searchBST(root, 54);

    EXPECT_EQ(root->data, 35);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);
    EXPECT_EQ(root->leftChild, node_10);
    EXPECT_EQ(root->rightChild, node_95);

    EXPECT_EQ(node_35, root);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, root);
    EXPECT_EQ(node_10->color, Color::RED);
    EXPECT_EQ(node_10->leftChild, node_1);
    EXPECT_EQ(node_10->rightChild, node_14);

    EXPECT_EQ(node_95->data, 95);
    EXPECT_EQ(node_95->parent, root);
    EXPECT_EQ(node_95->color, Color::RED);
    EXPECT_EQ(node_95->leftChild, node_58);
    EXPECT_EQ(node_95->rightChild, node_99);

    EXPECT_EQ(node_1->data, 1);
    EXPECT_EQ(node_1->parent, node_10);
    EXPECT_EQ(node_1->color, Color::BLACK);
    EXPECT_EQ(node_1->leftChild, nullptr);
    EXPECT_EQ(node_1->rightChild, nullptr);

    EXPECT_EQ(node_14->data, 14);
    EXPECT_EQ(node_14->parent, node_10);
    EXPECT_EQ(node_14->color, Color::BLACK);
    EXPECT_EQ(node_14->leftChild, nullptr);
    EXPECT_EQ(node_14->rightChild, nullptr);

    EXPECT_EQ(node_58->data, 58);
    EXPECT_EQ(node_58->parent, node_95);
    EXPECT_EQ(node_58->color, Color::BLACK);
    EXPECT_EQ(node_58->leftChild, node_54);
    EXPECT_EQ(node_58->rightChild, nullptr);

    EXPECT_EQ(node_99->data, 99);
    EXPECT_EQ(node_99->parent, node_95);
    EXPECT_EQ(node_99->color, Color::BLACK);
    EXPECT_EQ(node_99->leftChild, nullptr);
    EXPECT_EQ(node_99->rightChild, nullptr);

    EXPECT_EQ(node_54->data, 54);
    EXPECT_EQ(node_54->parent, node_58);
    EXPECT_EQ(node_54->color, Color::RED);
    EXPECT_EQ(node_54->leftChild, nullptr);
    EXPECT_EQ(node_54->rightChild, nullptr);

    EXPECT_TRUE(isRedBlackTreeValid(root));
}

// Rotation operations.

TEST_F(RBTreeTestInt, FourNodesRecoloringPipeline)
{
    auto* node_1 = new RBNode(10);
    EXPECT_EQ(node_1->data, 10);
    EXPECT_EQ(node_1->parent, nullptr);
    EXPECT_EQ(node_1->color, Color::BLACK);
    //

    insertRB(node_1, 5);
    auto* node_2 = node_1->leftChild;
    EXPECT_EQ(node_2->data, 5);
    EXPECT_EQ(node_2->parent, node_1);
    EXPECT_EQ(node_2->color, Color::RED);
    //

    insertRB(node_1, 20);
    auto* node_3 = node_1->rightChild;
    EXPECT_EQ(node_3->data, 20);
    EXPECT_EQ(node_3->parent, node_1);
    EXPECT_EQ(node_3->color, Color::RED);

    // Applying recoloring.
    insertRB(node_1, 25);
    auto* node_4 = node_3->rightChild;

    EXPECT_EQ(node_2->data, 5);
    EXPECT_EQ(node_2->parent, node_1);
    EXPECT_EQ(node_2->color, Color::BLACK);

    EXPECT_EQ(node_3->data, 20);
    EXPECT_EQ(node_3->parent, node_1);
    EXPECT_EQ(node_3->color, Color::BLACK);

    EXPECT_EQ(node_4->data, 25);
    EXPECT_EQ(node_4->parent, node_3);
    EXPECT_EQ(node_4->parent->color, Color::BLACK);
    EXPECT_EQ(node_4->color, Color::RED);

    EXPECT_EQ(getUncle(node_4), node_2);
    EXPECT_EQ(getUncle(node_4)->color, Color::BLACK);
}

TEST_F(RBTreeTestInt, RotationWithLLRotation)
{
    //
    root = new RBNode(30);
    auto* node_30 = root;
    EXPECT_EQ(root->data, 30);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);

    //
    insertRB(root, 20);
    auto* node_20 = searchBST(root, 20);
    EXPECT_EQ(node_20->data, 20);
    EXPECT_EQ(node_20->parent, node_30);
    EXPECT_EQ(node_20->color, Color::RED);

    // Trigger LLRotation
    insertRB(root, 10);
    auto node_10 = searchBST(root, 10);
    ;

    EXPECT_EQ(node_20->data, 20);
    EXPECT_EQ(node_20->parent, nullptr);
    EXPECT_EQ(node_20->color, Color::BLACK);
    EXPECT_EQ(node_20->leftChild, node_10);
    EXPECT_EQ(node_20->rightChild, node_30);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, node_20);
    EXPECT_EQ(node_10->color, Color::RED);
    EXPECT_EQ(node_10->leftChild, nullptr);
    EXPECT_EQ(node_10->rightChild, nullptr);

    EXPECT_EQ(node_30->data, 30);
    EXPECT_EQ(node_30->parent, node_20);
    EXPECT_EQ(node_30->color, Color::RED);
    EXPECT_EQ(node_30->leftChild, nullptr);
    EXPECT_EQ(node_30->rightChild, nullptr);
}

TEST_F(RBTreeTestInt, RotationWithRRRotation)
{
    //
    root = new RBNode(10);
    auto* node_10 = root;
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);

    //
    insertRB(root, 20);
    auto* node_20 = searchBST(root, 20);
    EXPECT_EQ(node_20->data, 20);
    EXPECT_EQ(node_20->parent, node_10);
    EXPECT_EQ(node_20->color, Color::RED);

    // Trigger RRRotation
    insertRB(root, 30);
    auto node_30 = searchBST(root, 30);

    EXPECT_EQ(node_20->data, 20);
    EXPECT_EQ(node_20->parent, nullptr);
    EXPECT_EQ(node_20->color, Color::BLACK);
    EXPECT_EQ(node_20->leftChild, node_10);
    EXPECT_EQ(node_20->rightChild, node_30);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, node_20);
    EXPECT_EQ(node_10->color, Color::RED);
    EXPECT_EQ(node_10->leftChild, nullptr);
    EXPECT_EQ(node_10->rightChild, nullptr);

    EXPECT_EQ(node_30->data, 30);
    EXPECT_EQ(node_30->parent, node_20);
    EXPECT_EQ(node_30->color, Color::RED);
    EXPECT_EQ(node_30->leftChild, nullptr);
    EXPECT_EQ(node_30->rightChild, nullptr);
}

TEST_F(RBTreeTestInt, RotationWithLRRotation)
{
    //
    root = new RBNode(30);
    auto* node_30 = root;
    EXPECT_EQ(root->data, 30);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);

    //
    insertRB(root, 10);
    auto* node_10 = searchBST(root, 10);
    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, node_30);
    EXPECT_EQ(node_10->color, Color::RED);

    // Trigger LRRotation
    insertRB(root, 20);
    auto* node_20 = searchBST(root, 20);

    EXPECT_EQ(node_20->data, 20);
    EXPECT_EQ(node_20->parent, nullptr);
    EXPECT_EQ(node_20->color, Color::BLACK);
    EXPECT_EQ(node_20->leftChild, node_10);
    EXPECT_EQ(node_20->rightChild, node_30);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, node_20);
    EXPECT_EQ(node_10->color, Color::RED);
    EXPECT_EQ(node_10->leftChild, nullptr);
    EXPECT_EQ(node_10->rightChild, nullptr);

    EXPECT_EQ(node_30->data, 30);
    EXPECT_EQ(node_30->parent, node_20);
    EXPECT_EQ(node_30->color, Color::RED);
    EXPECT_EQ(node_30->leftChild, nullptr);
    EXPECT_EQ(node_30->rightChild, nullptr);
}

TEST_F(RBTreeTestInt, RotationWithRLRotation)
{
    //
    root = new RBNode(10);
    auto* node_10 = root;
    EXPECT_EQ(root->data, 10);
    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->color, Color::BLACK);

    //
    insertRB(node_10, 30);
    auto* node_30 = searchBST(root, 30);
    EXPECT_EQ(node_30->data, 30);
    EXPECT_EQ(node_30->parent, node_10);
    EXPECT_EQ(node_30->color, Color::RED);

    // Trigger LRRotation
    insertRB(root, 20);
    auto* node_20 = searchBST(root, 20);

    EXPECT_EQ(node_20->data, 20);
    EXPECT_EQ(node_20->parent, nullptr);
    EXPECT_EQ(node_20->color, Color::BLACK);
    EXPECT_EQ(node_20->leftChild, node_10);
    EXPECT_EQ(node_20->rightChild, node_30);

    EXPECT_EQ(node_10->data, 10);
    EXPECT_EQ(node_10->parent, node_20);
    EXPECT_EQ(node_10->color, Color::RED);
    EXPECT_EQ(node_10->leftChild, nullptr);
    EXPECT_EQ(node_10->rightChild, nullptr);

    EXPECT_EQ(node_30->data, 30);
    EXPECT_EQ(node_30->parent, node_20);
    EXPECT_EQ(node_30->color, Color::RED);
    EXPECT_EQ(node_30->leftChild, nullptr);
    EXPECT_EQ(node_30->rightChild, nullptr);
}

TEST_F(RBTreeTestInt, InsertThreeNodesLL_ShouldTriggerLLRotation)
{
    insertRB(root, 10);
    insertRB(root, 5);
    insertRB(root, 2);  // Should trigger LL rotation

    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(isRedBlackTreeValid(root));
    EXPECT_EQ(root->data, 5);
    EXPECT_EQ(root->color, Color::BLACK);
    EXPECT_EQ(root->leftChild->data, 2);
    EXPECT_EQ(root->rightChild->data, 10);
}

TEST_F(RBTreeTestInt, InsertThreeNodesRR_ShouldTriggerRRRotation)
{
    insertRB(root, 10);
    insertRB(root, 15);
    insertRB(root, 20);  // Should trigger RR rotation

    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(isRedBlackTreeValid(root));
    EXPECT_EQ(root->data, 15);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 20);
}

TEST_F(RBTreeTestInt, InsertThreeNodesLR_ShouldTriggerLRRotation)
{
    insertRB(root, 10);
    insertRB(root, 5);
    insertRB(root, 7);  // Should trigger LR rotation

    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(isRedBlackTreeValid(root));
    EXPECT_EQ(root->data, 7);
    EXPECT_EQ(root->leftChild->data, 5);
    EXPECT_EQ(root->rightChild->data, 10);
}

TEST_F(RBTreeTestInt, InsertThreeNodesRL_ShouldTriggerRLRotation)
{
    insertRB(root, 10);
    insertRB(root, 15);
    insertRB(root, 13);  // Should trigger RL rotation

    ASSERT_NE(root, nullptr);
    EXPECT_TRUE(isRedBlackTreeValid(root));
    EXPECT_EQ(root->data, 13);
    EXPECT_EQ(root->leftChild->data, 10);
    EXPECT_EQ(root->rightChild->data, 15);
}

// RANDOM

TEST(RandomRBTreeTest, InsertRandomUniqueValuesWithTimeSeed_ShouldRemainValid)
{
    RBNode<int>* root_test = nullptr;

    std::set<int> insertedValues;

    // Seed RNG with current time
    auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, 1000);

    const int NUM_INSERTS = 1000;

    for (int i = 0; i < NUM_INSERTS; ++i)
    {
        int val;
        do
        {
            val = dist(rng);
        } while (!insertedValues.insert(val).second);  // ensure uniqueness

        insertRB(root_test, val);
        std::cout << "Inserted: " << val << "\n";
        ASSERT_TRUE(isRedBlackTreeValid(root_test)) << "[Insert Nº " << i << "]Tree invalid after inserting: " << val;
    }

    EXPECT_TRUE(isRedBlackTreeValid(root_test));
    std::cout << "Inserted " << insertedValues.size() << " unique values using seed " << seed << ".\n";

    delete root_test;
}