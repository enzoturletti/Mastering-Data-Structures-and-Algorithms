#include <gtest/gtest.h>
#include <algorithm>  // For std::sort and std::unique
#include <permutation.hpp>
#include <set>  // For std::set

// Utility to check if two vectors contain the same elements, regardless of order
void AssertPermutationResults(const std::vector<std::string>& result, const std::vector<std::string>& expected)
{
    std::vector<std::string> sortedResult = result;
    std::vector<std::string> sortedExpected = expected;

    std::sort(sortedResult.begin(), sortedResult.end());
    std::sort(sortedExpected.begin(), sortedExpected.end());

    ASSERT_EQ(sortedResult, sortedExpected);
}

// Unit Test for empty string
TEST(PermutationTests, HandlesEmptyString)
{
    std::vector<std::string> expected = {""};  // By convention, one empty permutation
    auto result = permutation("");
    AssertPermutationResults(result, expected);
}

// Unit Test for single character
TEST(PermutationTests, HandlesSingleCharacter)
{
    std::vector<std::string> expected = {"a"};
    auto result = permutation("a");
    AssertPermutationResults(result, expected);
}

// Unit Test for two characters
TEST(PermutationTests, HandlesTwoCharacters)
{
    std::vector<std::string> expected = {"ab", "ba"};
    auto result = permutation("ab");
    AssertPermutationResults(result, expected);
}

// Unit Test for three characters
TEST(PermutationTests, HandlesThreeCharacters)
{
    std::vector<std::string> expected = {"abc", "acb", "bac", "bca", "cab", "cba"};
    auto result = permutation("abc");
    AssertPermutationResults(result, expected);
}

// Unit Test for four characters
TEST(PermutationTests, HandlesFourCharacters)
{
    std::vector<std::string> expected = {"abcd", "abdc", "acbd", "acdb", "adbc", "adcb", "bacd", "badc",
                                         "bcad", "bcda", "bdac", "bdca", "cabd", "cadb", "cbad", "cbda",
                                         "cdab", "cdba", "dabc", "dacb", "dbac", "dbca", "dcab", "dcba"};
    auto result = permutation("abcd");
    AssertPermutationResults(result, expected);
}

// Unit Test for longer string (performance and correctness)
TEST(PermutationTests, HandlesLargerStrings)
{
    std::string input = "abcde";  // Larger input
    auto result = permutation(input);

    // Validate size
    size_t expectedSize = 120;  // 5! = 120
    ASSERT_EQ(result.size(), expectedSize);

    // Ensure all permutations are unique
    std::set<std::string> uniquePermutations(result.begin(), result.end());
    ASSERT_EQ(result.size(), uniquePermutations.size());
}

TEST(PermutationTests, HandlesDuplicateCharacters)
{
    // Input with duplicate characters
    std::string input = "aabc";

    // Generate permutations
    auto result = permutation(input);

    // Step 1: Verify the size of the result
    // The expected number of unique permutations is 4! / (2!) = 12
    size_t expectedSize = 12;
    ASSERT_EQ(result.size(), expectedSize) << "The number of permutations is incorrect.";

    // Step 2: Use a set to ensure uniqueness
    std::set<std::string> uniquePermutations(result.begin(), result.end());
    ASSERT_EQ(result.size(), uniquePermutations.size()) << "Duplicate permutations found in the result.";

    // Step 3: Verify all expected permutations are present
    std::vector<std::string> expected = {"aabc", "aacb", "abac", "abca", "acab", "acba",
                                         "baac", "baca", "bcaa", "caab", "caba", "cbaa"};

    // Sort both the result and expected vectors for comparison
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());

    ASSERT_EQ(result, expected) << "The permutations do not match the expected output.";

    // Step 4: Print permutations for debugging (optional)
    for (const auto& perm : result)
    {
        std::cout << perm << "\n";
    }
}

// Unit Test to verify behavior with special characters
TEST(PermutationTests, HandlesSpecialCharacters)
{
    std::string input = "a@1";
    std::vector<std::string> expected = {"a@1", "a1@", "@a1", "@1a", "1a@", "1@a"};
    auto result = permutation(input);
    AssertPermutationResults(result, expected);
}

// Unit Test for numeric characters
TEST(PermutationTests, HandlesNumericCharacters)
{
    std::string input = "123";
    std::vector<std::string> expected = {"123", "132", "213", "231", "312", "321"};
    auto result = permutation(input);
    AssertPermutationResults(result, expected);
}
