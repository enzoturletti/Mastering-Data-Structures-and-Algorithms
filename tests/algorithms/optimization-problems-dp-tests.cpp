#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <optimization-problems-dp.hpp>

/////////////////////////////////////////////////////////////

TEST(KnapsackTest, BasicSetMethod)
{
    ProfitWeightVector items = {
        {1, 2},  // profit 1, weight 2
        {2, 3},  // profit 2, weight 3
        {5, 4},  // profit 5, weight 4
        {6, 5}   // profit 6, weight 5
    };

    uint16_t capacity = 8;
    auto chosen = KnapSackAlgorithmSetMethod(items, capacity);

    // The best solution is items 1 and 3 (profits 2 + 6 = 8, weights 3 + 5 = 8)
    std::vector<bool> expected = {false, true, false, true};

    EXPECT_EQ(chosen, expected);
}

TEST(KnapsackTest, EmptyInput)
{
    ProfitWeightVector items = {};
    uint16_t capacity = 10;
    auto chosen = KnapSackAlgorithmSetMethod(items, capacity);
    EXPECT_TRUE(chosen.empty());
}

TEST(KnapsackTest, ZeroCapacity)
{
    ProfitWeightVector items = {{10, 1}, {20, 2}};
    uint16_t capacity = 0;
    auto chosen = KnapSackAlgorithmSetMethod(items, capacity);
    std::vector<bool> expected = {false, false};
    EXPECT_EQ(chosen, expected);
}

TEST(KnapsackTest, AllItemsFit)
{
    ProfitWeightVector items = {{3, 1}, {4, 2}, {5, 2}};
    uint16_t capacity = 10;  // big enough to take all
    auto chosen = KnapSackAlgorithmSetMethod(items, capacity);
    std::vector<bool> expected = {true, true, true};
    EXPECT_EQ(chosen, expected);
}

TEST(KnapsackTest, LargeProfitsSmallWeights)
{
    ProfitWeightVector items = {{900, 1}, {2000, 2}, {3000, 3}, {4000, 4}};
    uint16_t capacity = 5;
    auto chosen = KnapSackAlgorithmSetMethod(items, capacity);

    // Best choice is items 1 and 2 (weights 2+3=5, profits 2000+3000=5000)
    std::vector<bool> expected = {false, true, true, false};
    EXPECT_EQ(chosen, expected);
}

TEST(KnapsackTest, MultipleOptimalSolutions)
{
    ProfitWeightVector items = {{6, 4}, {6, 4}, {5, 3}};
    uint16_t capacity = 7;

    auto chosen = KnapSackAlgorithmSetMethod(items, capacity);

    // Multiple optimal solutions possible (choose first two items or last two)
    // Check profit is maximal (11)
    uint16_t totalProfit = 0;
    uint16_t totalWeight = 0;
    for (size_t i = 0; i < chosen.size(); ++i)
    {
        if (chosen[i])
        {
            totalProfit += items[i].first;
            totalWeight += items[i].second;
        }
    }

    EXPECT_LE(totalWeight, capacity);
    EXPECT_EQ(totalProfit, 11);
}

/////////////////////////////////////////////////////////////

TEST(KnapsackRecursiveTest, Basic)
{
    ProfitWeightVector items = {{1, 2}, {2, 3}, {5, 4}, {6, 5}};

    uint16_t capacity = 8;
    uint16_t result = KnapSackAlgorithmRecursiveMethod(items, capacity);

    EXPECT_EQ(result, 8);  // items 1 + 3
}

TEST(KnapsackRecursiveTest, EmptyInput)
{
    ProfitWeightVector items = {};
    uint16_t capacity = 10;
    uint16_t result = KnapSackAlgorithmRecursiveMethod(items, capacity);

    EXPECT_EQ(result, 0);
}

TEST(KnapsackRecursiveTest, ZeroCapacity)
{
    ProfitWeightVector items = {{10, 1}, {20, 2}};
    uint16_t capacity = 0;
    uint16_t result = KnapSackAlgorithmRecursiveMethod(items, capacity);

    EXPECT_EQ(result, 0);
}

TEST(KnapsackRecursiveTest, AllItemsFit)
{
    ProfitWeightVector items = {{3, 1}, {4, 2}, {5, 2}};
    uint16_t capacity = 10;
    uint16_t result = KnapSackAlgorithmRecursiveMethod(items, capacity);

    EXPECT_EQ(result, 12);  // 3 + 4 + 5
}

TEST(KnapsackRecursiveTest, LargeProfitsSmallWeights)
{
    ProfitWeightVector items = {{900, 1}, {2000, 2}, {3000, 3}, {4000, 4}};
    uint16_t capacity = 5;
    uint16_t result = KnapSackAlgorithmRecursiveMethod(items, capacity);

    EXPECT_EQ(result, 5000);  // items 1 + 2
}

TEST(KnapsackRecursiveTest, MultipleOptimalSolutions)
{
    ProfitWeightVector items = {{6, 4}, {6, 4}, {5, 3}};
    uint16_t capacity = 7;
    uint16_t result = KnapSackAlgorithmRecursiveMethod(items, capacity);

    EXPECT_EQ(result, 11);  // multiple valid subsets give 11
}

/////////////////////////////////////////////////////////////

TEST(KnapsackRecursiveTestWithMemo, Basic)
{
    ProfitWeightVector items = {{1, 2}, {2, 3}, {5, 4}, {6, 5}};
    uint16_t capacity = 8;

    auto [result, included] = KnapSackAlgorithmRecursiveMethodWithMemorization(items, capacity);

    EXPECT_EQ(result, 8);  // items 1 + 3
}

TEST(KnapsackRecursiveTestWithMemo, EmptyInput)
{
    ProfitWeightVector items = {};
    uint16_t capacity = 10;

    auto [result, included] = KnapSackAlgorithmRecursiveMethodWithMemorization(items, capacity);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(included.empty());
}

TEST(KnapsackRecursiveTestWithMemo, ZeroCapacity)
{
    ProfitWeightVector items = {{10, 1}, {20, 2}};
    uint16_t capacity = 0;

    auto [result, included] = KnapSackAlgorithmRecursiveMethodWithMemorization(items, capacity);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(included, std::vector<bool>({false, false}));
}

TEST(KnapsackRecursiveTestWithMemo, AllItemsFit)
{
    ProfitWeightVector items = {{3, 1}, {4, 2}, {5, 2}};
    uint16_t capacity = 10;

    auto [result, included] = KnapSackAlgorithmRecursiveMethodWithMemorization(items, capacity);

    EXPECT_EQ(result, 12);  // 3 + 4 + 5
    EXPECT_EQ(included, std::vector<bool>({true, true, true}));
}

TEST(KnapsackRecursiveTestWithMemo, LargeProfitsSmallWeights)
{
    ProfitWeightVector items = {{900, 1}, {2000, 2}, {3000, 3}, {4000, 4}};
    uint16_t capacity = 5;

    auto [result, included] = KnapSackAlgorithmRecursiveMethodWithMemorization(items, capacity);

    EXPECT_EQ(result, 5000);  // items 2 + 3
    EXPECT_EQ(included, std::vector<bool>({false, true, true, false}));
}

TEST(KnapsackRecursiveTestWithMemo, MultipleOptimalSolutions)
{
    ProfitWeightVector items = {{6, 4}, {6, 4}, {5, 3}};
    uint16_t capacity = 7;

    auto [result, included] = KnapSackAlgorithmRecursiveMethodWithMemorization(items, capacity);

    EXPECT_EQ(result, 11);  // multiple valid subsets give 11

    // Since multiple subsets are valid, just assert the correct profit and valid inclusion
    // Any of these combinations is valid: (0 + 2) or (1 + 2)
    EXPECT_TRUE(
        (included == std::vector<bool>({true, false, true})) || (included == std::vector<bool>({false, true, true})));
}

/////////////////////////////////////////////////////////////

TEST(KnapsackTabulationMethod, Basic)
{
    ProfitWeightVector items = {{1, 2}, {2, 3}, {5, 4}, {6, 5}};
    uint16_t capacity = 8;

    auto [result, included] = KnapSackAlgorithmTabulationMethod(items, capacity);

    EXPECT_EQ(result, 8);  // items 1 + 3
}

TEST(KnapsackTabulationMethod, EmptyInput)
{
    ProfitWeightVector items = {};
    uint16_t capacity = 10;

    auto [result, included] = KnapSackAlgorithmTabulationMethod(items, capacity);

    EXPECT_EQ(result, 0);
    EXPECT_TRUE(included.empty());
}

TEST(KnapsackTabulationMethod, ZeroCapacity)
{
    ProfitWeightVector items = {{10, 1}, {20, 2}};
    uint16_t capacity = 0;

    auto [result, included] = KnapSackAlgorithmTabulationMethod(items, capacity);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(included, std::vector<bool>({false, false}));
}

TEST(KnapsackTabulationMethod, AllItemsFit)
{
    ProfitWeightVector items = {{3, 1}, {4, 2}, {5, 2}};
    uint16_t capacity = 10;

    auto [result, included] = KnapSackAlgorithmTabulationMethod(items, capacity);

    EXPECT_EQ(result, 12);  // 3 + 4 + 5
    EXPECT_EQ(included, std::vector<bool>({true, true, true}));
}

TEST(KnapsackTabulationMethod, LargeProfitsSmallWeights)
{
    ProfitWeightVector items = {{900, 1}, {2000, 2}, {3000, 3}, {4000, 4}};
    uint16_t capacity = 5;

    auto [result, included] = KnapSackAlgorithmTabulationMethod(items, capacity);

    EXPECT_EQ(result, 5000);  // items 2 + 3
    EXPECT_EQ(included, std::vector<bool>({false, true, true, false}));
}

TEST(KnapsackTabulationMethod, MultipleOptimalSolutions)
{
    ProfitWeightVector items = {{6, 4}, {6, 4}, {5, 3}};
    uint16_t capacity = 7;

    auto [result, included] = KnapSackAlgorithmTabulationMethod(items, capacity);

    EXPECT_EQ(result, 11);  // multiple valid subsets give 11

    // Since multiple subsets are valid, just assert the correct profit and valid inclusion
    // Any of these combinations is valid: (0 + 2) or (1 + 2)
    EXPECT_TRUE(
        (included == std::vector<bool>({true, false, true})) || (included == std::vector<bool>({false, true, true})));
}

/////////////////////////////////////////////////////////////

TEST(MatrixChainMultiplicationTest, RecursiveMethod)
{
    Matrix A = {{1, 2}, {3, 4}, {5, 6}};

    Matrix B = {{1, 2, 3, 4}, {5, 6, 7, 8}};

    Matrix C = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    Matrix D = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};

    MatrixChain chain = {A, B, C, D};

    EXPECT_EQ(MatrixChainMultiplicationRecursionMethod(chain), 58);
}

TEST(MatrixChainMultiplicationTest, RecursiveMethodWithMemo)
{
    Matrix A = {{1, 2}, {3, 4}, {5, 6}};

    Matrix B = {{1, 2, 3, 4}, {5, 6, 7, 8}};

    Matrix C = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    Matrix D = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};

    MatrixChain chain = {A, B, C, D};

    EXPECT_EQ(MatrixChainMultiplicationRecursionMethodWithMemorization(chain), 58);
}

TEST(MatrixChainMultiplicationTest, TabulationMethod)
{
    Matrix A = {{1, 2}, {3, 4}, {5, 6}};

    Matrix B = {{1, 2, 3, 4}, {5, 6, 7, 8}};

    Matrix C = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

    Matrix D = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};

    MatrixChain chain = {A, B, C, D};

    EXPECT_EQ(MatrixChainMultiplicationTabulationMethod(chain), 58);
}
