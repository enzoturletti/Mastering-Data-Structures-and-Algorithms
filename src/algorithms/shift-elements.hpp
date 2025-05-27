#pragma once

/**
 * @brief Shifts the elements of a range to the left by a specified number of positions in O(n) time.
 *
 * This function shifts elements of the container starting from the `begin` iterator to the `end` iterator to the left
 * by the specified number of positions. Elements that are shifted out of the range will be replaced by `0`.
 * The function ensures that if the number of positions exceeds the range size, it only shifts up to the range size.
 * If the number of positions is 0, the array remains unchanged.
 *
 * @tparam Iterator The type of iterator used (e.g., raw pointer or a more complex iterator type).
 * @param begin The iterator to the first element of the range.
 * @param end The iterator to the one-past-the-last element of the range.
 * @param positions The number of positions to shift elements to the left.
 *
 * @note If the range is empty, the function does nothing. If positions exceed the range size, the shift is limited
 *       to the array size.
 *
 * @complexity
 * - Time complexity: O(n), where n is the size of the range (`end - begin`).
 * - Space complexity: O(1), since the algorithm only uses a fixed amount of additional space regardless of the input
 * size.
 */
template <typename Iterator>
void leftShiftElements(Iterator begin, Iterator end, uint16_t positions)
{
    if (begin == end || positions == 0)
    {
        return;
    }

    uint16_t rangeSize = std::distance(begin, end);
    positions = std::min(positions, static_cast<uint16_t>(rangeSize));

    // Move all elements left by the specified number of positions
    Iterator current = begin;
    Iterator shiftBegin = begin + positions;
    while (shiftBegin != end)
    {
        *current = *shiftBegin;
        ++current;
        ++shiftBegin;
    }

    // Set the last 'positions' elements to zero
    while (current != end)
    {
        *current = {};
        ++current;
    }
}

/**
 * @brief Shifts the elements of a range to the right by a specified number of positions in O(n) time.
 *
 * This function shifts elements of the container starting from the `begin` iterator to the `end` iterator to the right
 * by the specified number of positions. Elements that are shifted out of the range will be replaced by `0`.
 * The function ensures that if the number of positions exceeds the range size, it only shifts up to the range size.
 * If the number of positions is 0, the array remains unchanged.
 *
 * @tparam Iterator The type of iterator used (e.g., raw pointer or a more complex iterator type).
 * @param begin The iterator to the first element of the range.
 * @param end The iterator to the one-past-the-last element of the range.
 * @param positions The number of positions to shift elements to the right.
 *
 * @note If the range is empty, the function does nothing. If positions exceed the range size, the shift is limited
 *       to the array size.
 *
 * @complexity
 * - Time complexity: O(n), where n is the size of the range (`end - begin`).
 * - Space complexity: O(1), since the algorithm only uses a fixed amount of additional space regardless of the input
 * size.
 */
template <typename Iterator>
void rightShiftElements(Iterator begin, Iterator end, uint16_t positions)
{
    if (begin == end || positions == 0)
    {
        return;
    }

    uint16_t rangeSize = std::distance(begin, end);
    positions = std::min(positions, static_cast<uint16_t>(rangeSize));

    // Move all elements right by the specified number of positions
    Iterator current = end - 1;
    Iterator shiftEnd = end - positions - 1;
    while (shiftEnd >= begin)
    {
        *current = *shiftEnd;
        --current;
        --shiftEnd;
    }

    // Set the first 'positions' elements to zero
    while (current >= begin)
    {
        *current = {};
        --current;
    }
}
