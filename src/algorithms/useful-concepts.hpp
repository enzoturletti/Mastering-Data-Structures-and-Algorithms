#pragma once

#include <concepts>
#include <type_traits>

/**
 * @brief Concept to check for the presence of begin() and end().
 *
 * This concept ensures that the type T has member functions `begin()` and `end()`.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasCustomBeginEnd = requires(T t)
{
    {t.begin()};  ///< Ensure begin() exists
    {t.end()};    ///< Ensure end() exists
};

/**
 * @brief Concept to check for the presence of getSize().
 *
 * This concept ensures that the type T has a member function `getSize()`.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetSize = requires(T t)
{
    {t.getSize()};  ///< Ensure getSize() exists
};

/**
 * @brief Concept to check for the presence of append().
 *
 * This concept ensures that the type T has a member function `append(const typename T::value_type&)`.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasAppend = requires(T t, typename T::value_type value)
{
    {t.append(value)};  ///< Ensure append() exists and accepts a value of T::value_type
};

/**
 * @brief Concept to check if T::value_type is an int.
 *
 * This concept ensures that the type T has a member type `value_type` that is exactly `int`.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasValueTypeInt = requires
{
    typename T::value_type;  ///< Ensure T has a member type `value_type`
}
&&std::is_same_v<typename T::value_type, int>;
