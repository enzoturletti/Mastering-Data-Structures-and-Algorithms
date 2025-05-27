#include <gtest/gtest.h>
#include <algorithm>  // For std::sort and std::unique
#include <combination.hpp>
#include <set>  // For std::set

// Utility to check if two vectors contain the same elements, regardless of order
void AssertCombinationResults(const std::vector<std::string>& result, const std::vector<std::string>& expected)
{
    std::vector<std::string> sortedResult = result;
    std::vector<std::string> sortedExpected = expected;

    std::sort(sortedResult.begin(), sortedResult.end());
    std::sort(sortedExpected.begin(), sortedExpected.end());

    ASSERT_EQ(sortedResult, sortedExpected);
}

// Unit Test for empty string and size 0
TEST(CombinationTests, HandlesEmptyStringAndSizeZero)
{
    std::vector<std::string> expected = {""};  // By convention, one empty combination
    auto result = combination("", 0);
    AssertCombinationResults(result, expected);
}

// Unit Test for single character and size 1
TEST(CombinationTests, HandlesSingleCharacterAndSizeOne)
{
    std::vector<std::string> expected = {"a"};
    auto result = combination("a", 1);
    AssertCombinationResults(result, expected);
}

// Unit Test for two characters and size 1
TEST(CombinationTests, HandlesTwoCharactersAndSizeOne)
{
    std::vector<std::string> expected = {"a", "b"};
    auto result = combination("ab", 1);
    AssertCombinationResults(result, expected);
}

// Unit Test for two characters and size 2
TEST(CombinationTests, HandlesTwoCharactersAndSizeTwo)
{
    std::vector<std::string> expected = {"ab"};
    auto result = combination("ab", 2);
    AssertCombinationResults(result, expected);
}

// Unit Test for three characters and size 2
TEST(CombinationTests, HandlesThreeCharactersAndSizeTwo)
{
    std::vector<std::string> expected = {"ab", "ac", "bc"};
    auto result = combination("abc", 2);
    AssertCombinationResults(result, expected);
}

// Unit Test for three characters and size 3
TEST(CombinationTests, HandlesThreeCharactersAndSizeThree)
{
    std::vector<std::string> expected = {"abc"};
    auto result = combination("abc", 3);
    AssertCombinationResults(result, expected);
}

// Unit Test for four characters and size 2
TEST(CombinationTests, HandlesFourCharactersAndSizeTwo)
{
    std::vector<std::string> expected = {"ab", "ac", "ad", "bc", "bd", "cd"};
    auto result = combination("abcd", 2);
    AssertCombinationResults(result, expected);
}

// Unit Test for combination size greater than input size (edge case)
TEST(CombinationTests, HandlesCombinationSizeGreaterThanInput)
{
    std::vector<std::string> expected = {};  // No combinations possible
    auto result = combination("abc", 4);
    AssertCombinationResults(result, expected);
}

// Unit Test for duplicate characters
TEST(CombinationTests, HandlesDuplicateCharacters)
{
    std::string input = "aabc";
    std::vector<std::string> expected = {"aa", "ab", "ac", "bc"};
    auto result = combination(input, 2);

    // Validate the size
    size_t expectedSize = 4;
    ASSERT_EQ(result.size(), expectedSize) << "The number of combinations is incorrect.";

    // Ensure all combinations are unique
    std::set<std::string> uniqueCombinations(result.begin(), result.end());
    ASSERT_EQ(result.size(), uniqueCombinations.size()) << "Duplicate combinations found in the result.";

    // Sort and compare both vectors
    AssertCombinationResults(result, expected);
}

// Unit Test to verify behavior with special characters
TEST(CombinationTests, HandlesSpecialCharacters)
{
    std::string input = "a@1";
    std::vector<std::string> expected = {"@a", "1a", "1@"};
    auto result = combination(input, 2);
    AssertCombinationResults(result, expected);
}

// Unit Test for numeric characters
TEST(CombinationTests, HandlesNumericCharacters)
{
    std::string input = "123";
    std::vector<std::string> expected = {"12", "13", "23"};
    auto result = combination(input, 2);
    AssertCombinationResults(result, expected);
}

// Unit Test for combination size equal to input size
TEST(CombinationTests, HandlesCombinationSizeEqualToInput)
{
    std::string input = "abcd";
    std::vector<std::string> expected = {"abcd"};
    auto result = combination(input, 4);
    AssertCombinationResults(result, expected);
}
