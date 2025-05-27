#pragma once

#include <shift-elements.hpp>

/**
 * @brief Rotates the elements in the range [begin, end) to the left by a given number of positions.
 *
 * This function shifts all the elements to the left by the specified number of positions,
 * wrapping the elements that are moved out of the beginning to the end of the range.
 * It works in a circular manner, where elements are "rotated" around.
 *
 * @tparam Iterator Type of the iterator (can be a raw pointer or any container iterator).
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 * @param positions The number of positions to rotate the elements to the left.
 *
 * @note If `positions` is greater than or equal to the size of the range,
 *       it will be reduced to `positions % size` to avoid unnecessary rotations.
 * @note This function uses the `leftShiftElements` helper function to move elements one position to the left.
 *
 * @complexity Time complexity: O(n), where n is the number of elements in the range.
 *               This is due to the shifting of elements once, and the insertion of the rotated values.
 * @complexity Space complexity: O(positions), where `positions` is the number of elements that will be rotated.
 *               This is due to the temporary storage for the rotated values.
 */
template <typename Iterator>
void leftRotateElements(Iterator begin, Iterator end, uint16_t positions)
{
    // Return early if range is empty or no rotation is needed.
    if (begin == end || positions == 0)
    {
        return;
    }

    // Minimum period to avoid redundant rotations
    uint16_t rangeSize = std::distance(begin, end);

    // Reduce positions to be within the range size (positions % rangeSize)
    positions = positions % rangeSize;

    // Use ValueType for cleaner code when handling element types
    using ValueType = typename std::iterator_traits<Iterator>::value_type;

    // Temporary vector to store the values that will be rotated to the back of the range
    std::vector<ValueType> tempRotatedValues(begin, begin + positions);

    // Shift the elements in the range [begin, end) to the left by `positions`
    leftShiftElements(begin, end, positions);

    // Insert the saved values into the newly vacant positions at the end of the range
    Iterator beginSavedValues = end - positions;
    for (ValueType savedValue : tempRotatedValues)
    {
        *beginSavedValues = savedValue;
        ++beginSavedValues;
    }
}

/**
 * @brief Rotates the elements in the range [begin, end) to the right by a given number of positions.
 *
 * This function shifts all the elements to the right by the specified number of positions,
 * wrapping the elements that are moved out of the end to the beginning of the range.
 * It works in a circular manner, where elements are "rotated" around.
 *
 * @tparam Iterator Type of the iterator (can be raw pointer or any container iterator).
 * @param begin Iterator pointing to the start of the range.
 * @param end Iterator pointing to the end of the range.
 * @param positions The number of positions to rotate the elements to the right.
 *
 * @note If `positions` is greater than or equal to the size of the range, it will be reduced to
 *       `positions % size` to avoid unnecessary rotations.
 * @note This function uses the `rightShiftElements` helper function to move elements one position to the right.
 *
 * @complexity Time complexity: O(n), where n is the number of elements in the range. This is due to the shifting of
 * elements and inserting the saved values into the correct positions. The time complexity is linear in the number of
 * elements in the range.
 * @complexity Space complexity: O(n), where n is the number of elements in the range, since we store the temporary
 * rotated elements in a vector of size `positions`.
 */
template <typename Iterator>
void rightRotateElements(Iterator begin, Iterator end, uint16_t positions)
{
    // Return early if range is empty or no rotation is needed.
    if (begin == end || positions == 0)
    {
        return;
    }

    // Minimum period to avoid redundant rotations
    uint16_t rangeSize = std::distance(begin, end);

    // Reduce positions to be within the range size (positions % rangeSize)
    positions = positions % rangeSize;

    // Use ValueType for cleaner code when handling element types
    using ValueType = typename std::iterator_traits<Iterator>::value_type;

    // Temporary vector to store the values that will be rotated to the back of the range
    std::vector<ValueType> tempRotatedValues(end - positions, end);

    // Shift the elements in the range [begin, end) to the left by `positions`
    rightShiftElements(begin, end, positions);

    // Insert the saved values into the newly vacant positions at the end of the range
    Iterator endSavedValues = begin;
    for (ValueType savedValue : tempRotatedValues)
    {
        *endSavedValues = savedValue;
        ++endSavedValues;
    }
}
