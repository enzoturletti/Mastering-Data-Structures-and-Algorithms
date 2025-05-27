#pragma once

#include <list.hpp>
#include <optional>
#include <static-array.hpp>
#include <utility>

/**
 * @brief A simple hash map implementation using separate chaining with a fixed number of buckets.
 *
 * @tparam T Type of the value to be stored.
 * @tparam BUCKETS Number of buckets used for hashing.
 */
template <typename T, size_t BUCKETS = 16>
class UnorderedMap
{
public:
    /**
     * @brief Inserts or updates the value associated with the given key.
     *
     * If the key already exists, the value is updated. Otherwise, the key-value pair is inserted.
     *
     * @param key The key to insert or update.
     * @param value The value to associate with the key.
     *
     * @note Assumes StaticArray and List support append() and iteration.
     *
     * @complexity
     * Time: O(N/B) average, O(N) worst-case (N = elements in map, B = buckets).
     * Space: O(1) additional.
     */
    void insert(uint8_t key, const T& value)
    {
        const size_t bucket_id = hashFunction(key);
        for (auto& [k, v] : mBuckets[bucket_id])
        {
            if (k == key)
            {
                v = value;  // Update existing key
                return;
            }
        }
        mBuckets[bucket_id].append({key, value});  // Insert new key-value pair
        ++mSize;
    }

    /**
     * @brief Removes the key-value pair associated with the given key.
     *
     * Does nothing if the key is not found.
     *
     * @param key The key to erase.
     *
     * @complexity
     * Time: O(N/B) average, O(N) worst-case.
     * Space: O(1)
     */
    void erase(uint8_t key)
    {
        const size_t bucket_id = hashFunction(key);
        auto& bucket = mBuckets[bucket_id];

        int index{-1};
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            index++;
            if (it->first == key)
            {
                bucket.erase(index);
                --mSize;
                return;
            }
        }
    }

    /**
     * @brief Finds the value associated with a given key.
     *
     * @param key The key to look up.
     * @return std::optional<T> containing the value if found, otherwise std::nullopt.
     *
     * @complexity
     * Time: O(N/B) average, O(N) worst-case.
     * Space: O(1)
     */
    [[nodiscard]] std::optional<T> find(uint8_t key) const
    {
        const size_t bucket_id = hashFunction(key);
        for (const auto& [k, v] : mBuckets[bucket_id])
        {
            if (k == key)
            {
                return v;
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Returns the current load factor of the hash table.
     *
     * Load factor is defined as size / number of buckets.
     *
     * @return float Load factor of the unordered_map.
     *
     * @complexity
     * Time: O(1)
     * Space: O(1)
     */
    [[nodiscard]] float loadFactor() const
    {
        return static_cast<float>(mSize) / BUCKETS;
    }

private:
    /**
     * @brief Computes the bucket index for a given key using modulo hashing.
     *
     * @param key The key to hash.
     * @return size_t The bucket index.
     *
     * @complexity
     * Time: O(1)
     * Space: O(1)
     */
    [[nodiscard]] size_t hashFunction(uint8_t key) const
    {
        return key % BUCKETS;
    }

    StaticArray<List<std::pair<uint8_t, T>>, BUCKETS> mBuckets;  ///< Array of buckets containing key-value lists.
    size_t mSize = 0;                                            ///< Number of key-value pairs in the map.
};