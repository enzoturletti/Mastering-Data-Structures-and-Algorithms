#include <gtest/gtest.h>

#include <parentheses-matching.hpp>
#include <stack.hpp>
#include <string>

/**
 * @brief Unit tests for parenthesesMatchs function.
 */

// Test for empty input
TEST(ParenthesesMatchTest, EmptyString)
{
    EXPECT_TRUE(parenthesesMatchs(""));
}

// Test for correctly matched parentheses, brackets, and braces
TEST(ParenthesesMatchTest, CorrectlyMatched)
{
    EXPECT_TRUE(parenthesesMatchs("()"));
    EXPECT_TRUE(parenthesesMatchs("[]"));
    EXPECT_TRUE(parenthesesMatchs("{}"));
    EXPECT_FALSE(parenthesesMatchs("({[]})"));
    EXPECT_FALSE(parenthesesMatchs("({[()]})"));
    EXPECT_TRUE(parenthesesMatchs("{{[[(())]]}}"));  // Complex nested, valid
}

// Test for incorrectly matched symbols
TEST(ParenthesesMatchTest, IncorrectlyMatched)
{
    EXPECT_FALSE(parenthesesMatchs("("));
    EXPECT_FALSE(parenthesesMatchs(")"));
    EXPECT_FALSE(parenthesesMatchs("{"));
    EXPECT_FALSE(parenthesesMatchs("}"));
    EXPECT_FALSE(parenthesesMatchs("["));
    EXPECT_FALSE(parenthesesMatchs("]"));
    EXPECT_FALSE(parenthesesMatchs("(()"));
    EXPECT_FALSE(parenthesesMatchs("())"));
    EXPECT_FALSE(parenthesesMatchs("{[}]"));    // Incorrectly nested
    EXPECT_FALSE(parenthesesMatchs("{[(])}"));  // Wrong order (incorrect hierarchy)
    EXPECT_FALSE(parenthesesMatchs("{[[}"));    // Mismatched brackets
}

// Test with non-parenthesis characters
TEST(ParenthesesMatchTest, WithOtherCharacters)
{
    EXPECT_TRUE(parenthesesMatchs("a + (b * c) - {d / [e + f]}"));
    EXPECT_FALSE(parenthesesMatchs("a + (b * c - {d / e)]"));  // Incorrect closing
    EXPECT_FALSE(parenthesesMatchs("a + b} * c("));            // Incorrect order
}

// Test for nested and complex cases
TEST(ParenthesesMatchTest, ComplexCases)
{
    EXPECT_TRUE(parenthesesMatchs("{[(a + b) * [c - (d + e)]]}"));  // Right order
    EXPECT_FALSE(parenthesesMatchs("((a + b) * [c - {d + e}])"));   // Wrong order
    EXPECT_FALSE(parenthesesMatchs("(((a + b)]"));                  // Mixed incorrect
    EXPECT_FALSE(parenthesesMatchs("(a + b]})"));                   // Wrong nesting
}

// Test for incorrect order cases (strict order of { before [ before ( must be maintained)
TEST(ParenthesesMatchTest, IncorrectOrder)
{
    EXPECT_FALSE(parenthesesMatchs(")("));    // Closing before opening
    EXPECT_FALSE(parenthesesMatchs("]["));    // Incorrect order of brackets
    EXPECT_FALSE(parenthesesMatchs("}{"));    // Incorrect order of braces
    EXPECT_FALSE(parenthesesMatchs("{[}"));   // Order violation: } after {
    EXPECT_FALSE(parenthesesMatchs("[(])"));  // Order violation: ] after (
}

// Test for extra opening symbols
TEST(ParenthesesMatchTest, ExtraOpening)
{
    EXPECT_FALSE(parenthesesMatchs("(()"));
    EXPECT_FALSE(parenthesesMatchs("{{"));
    EXPECT_FALSE(parenthesesMatchs("[[["));
}

// Test for extra closing symbols
TEST(ParenthesesMatchTest, ExtraClosing)
{
    EXPECT_FALSE(parenthesesMatchs("())"));
    EXPECT_FALSE(parenthesesMatchs("}}"));
    EXPECT_FALSE(parenthesesMatchs("]]]"));
}

// Test for complex incorrect nesting
TEST(ParenthesesMatchTest, ComplexIncorrect)
{
    EXPECT_FALSE(parenthesesMatchs("(()))(()"));
    EXPECT_FALSE(parenthesesMatchs("({)}"));     // Wrong closing order, mismatched
    EXPECT_FALSE(parenthesesMatchs("}{[(])}"));  // Incorrect order and nesting
}
