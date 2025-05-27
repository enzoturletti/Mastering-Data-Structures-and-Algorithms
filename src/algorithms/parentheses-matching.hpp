
#pragma once

#include <stack.hpp>
#include <string>

/**
 * @brief Checks if parentheses, brackets, and braces in a given string are correctly matched and ordered.
 *
 * This function ensures that every opening symbol ('(', '{', '[') has a corresponding and correctly ordered
 * closing symbol (')', '}', ']') in a valid nested structure. It distinguishes between different types of
 * parentheses and enforces a strict order of nesting. Non-parenthesis characters are ignored.
 *
 * @param input The input string to check.
 * @return True if all symbols are correctly matched, properly ordered, and properly nested; otherwise false.
 *
 * @note The function ensures that:
 * - Every opening parenthesis, bracket, or brace is closed by the correct matching symbol.
 * - The nesting order is strictly enforced: `{` must come before `[`, and `[` must come before `(`.
 *
 * @complexity Time: O(n), where n is the length of the input string (each character is processed once).
 * Space: O(n) in the worst case (when all characters are opening symbols and must be stored).
 */
bool parenthesesMatchs(const std::string& input)
{
    Stack<char> counter;

    for (char letter : input)
    {
        if (letter == '{' || letter == '[' || letter == '(')
        {
            if (!counter.isEmpty())
            {
                auto const top_letter = counter.top();

                const bool invalid_order = (top_letter == '(') && (letter == '[' || letter == '{') ||
                                           (top_letter == '[') && (letter == '{') ||
                                           (top_letter == '{') && (letter == '(');

                if (invalid_order)
                {
                    return false;  // Order is incorrect
                }
            }

            counter.push(letter);
        }
        else if (letter == '}' || letter == ']' || letter == ')')
        {
            if (counter.isEmpty())
            {
                return false;
            }

            auto top = counter.top();
            const bool valid_letter =
                (top == '{' && letter == '}') || (top == '[' && letter == ']') || (top == '(' && letter == ')');

            if (!valid_letter)
            {
                return false;
            }

            counter.pop();
        }
    }

    return counter.isEmpty();
}