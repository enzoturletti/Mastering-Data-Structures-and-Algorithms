#include <gtest/gtest.h>
#include <algorithm>
#include <backtracking.hpp>

////////////////////////////////////////////////////////////////////////////////////////

TEST(PermutationTest, UniqueCharacters)
{
    std::string input = "abc";
    auto result = permutations(input);

    std::vector<std::string> expected = {"abc", "acb", "bac", "bca", "cab", "cba"};

    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(result, expected);
}

TEST(PermutationTest, SingleCharacter)
{
    std::string input = "x";
    auto result = permutations(input);

    std::vector<std::string> expected = {"x"};

    EXPECT_EQ(result, expected);
}

TEST(PermutationTest, EmptyString)
{
    std::string input = "";
    auto result = permutations(input);

    std::vector<std::string> expected = {""};

    EXPECT_EQ(result, expected);
}

TEST(PermutationWithBoundingTest, UniqueCharacters)
{
    std::string input = "abc";
    auto result = permutationsWithBounding(input);

    std::vector<std::string> expected = {"acb", "bac", "cba"};

    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(result, expected);
}

TEST(PermutationWithBoundingTest, SingleCharacter)
{
    std::string input = "x";
    auto result = permutationsWithBounding(input);

    std::vector<std::string> expected = {"x"};

    EXPECT_EQ(result, expected);
}

TEST(PermutationWithBoundingTest, EmptyString)
{
    std::string input = "";
    auto result = permutationsWithBounding(input);

    std::vector<std::string> expected = {""};

    EXPECT_EQ(result, expected);
}

////////////////////////////////////////////////////////////////////////////////////////

// Helper function to validate a single solution
bool isValidSolution(const std::vector<uint8_t>& solution)
{
    int n = solution.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            // Check same column
            if (solution[i] == solution[j])
                return false;
            // Check diagonal conflicts
            if (abs(i - j) == abs((int)solution[i] - (int)solution[j]))
                return false;
        }
    }
    return true;
}

TEST(NQueensTest, KnownSolutionCounts)
{
    // Known number of solutions for small N
    struct TestCase
    {
        uint8_t N;
        int expectedSolutions;
    };
    std::vector<TestCase> testCases = {
        {1, 1}, {2, 0}, {3, 0}, {4, 2}, {5, 10},
    };

    for (const auto& testCase : testCases)
    {
        auto solutions = nQueensProblem(testCase.N);

        // Check the number of solutions is as expected
        EXPECT_EQ(solutions.size(), testCase.expectedSolutions) << "Failed for N=" << (int)testCase.N;

        // Validate all solutions are correct
        for (const auto& sol : solutions)
        {
            EXPECT_TRUE(isValidSolution(sol)) << "Invalid solution found for N=" << (int)testCase.N;
        }
    }
}

TEST(NQueensTest, LargerBoards)
{
    std::vector<uint8_t> largeBoards = {6, 7, 8, 9, 10};

    for (uint8_t N : largeBoards)
    {
        auto solutions = nQueensProblem(N);

        // Check that there is at least one solution
        EXPECT_GT(solutions.size(), 0) << "No solutions found for N=" << (int)N;

        // Validate each solution is correct
        for (const auto& sol : solutions)
        {
            EXPECT_TRUE(isValidSolution(sol)) << "Invalid solution found for N=" << (int)N;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////

TEST(RatInMazeTest, Simple2x2Path)
{
    Maze maze = {{true, true}, {false, true}};

    auto solutions = ratInAmaze(maze, 0, 0);

    ASSERT_EQ(solutions.size(), 1);
    EXPECT_EQ(solutions[0], MazeSolution({{0, 0}, {0, 1}, {1, 1}}));
}

TEST(RatInMazeTest, NoPathBlockedCell)
{
    Maze maze = {{true, false}, {false, true}};

    auto solutions = ratInAmaze(maze, 0, 0);
    EXPECT_TRUE(solutions.empty());
}

TEST(RatInMazeTest, Larger3x3MultiplePaths)
{
    Maze maze = {{true, true, true}, {false, true, false}, {true, true, true}};

    auto solutions = ratInAmaze(maze, 0, 0);
    ASSERT_FALSE(solutions.empty());

    for (const auto& path : solutions)
    {
        ASSERT_EQ(path.front(), std::make_pair(0, 0));
        ASSERT_EQ(path.back(), std::make_pair(2, 2));
    }
}

TEST(RatInMazeTest, StartBlocked)
{
    Maze maze = {{false, true}, {true, true}};

    auto solutions = ratInAmaze(maze, 0, 0);
    EXPECT_TRUE(solutions.empty());
}

TEST(RatInMazeTest, EndBlocked)
{
    Maze maze = {{true, true}, {true, false}};

    auto solutions = ratInAmaze(maze, 0, 0);
    EXPECT_TRUE(solutions.empty());
}
