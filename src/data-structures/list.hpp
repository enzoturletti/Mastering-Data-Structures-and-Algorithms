#pragma once

#include <initializer_list>
#include <iterator>

/**
 * @brief Represents a node in the doubly linked list.
 *
 * @tparam T The type of the node's value.
 */
template <typename T>
struct Node
{
    T value;                 ///< The value of the node.
    Node<T>* next{nullptr};  ///< Pointer to the next node in the list.
    Node<T>* prev{nullptr};  ///< Pointer to the previous node in the list.

    /**
     * @brief Constructs a new Node with the given value.
     *
     * @param _value The value to be stored in the node.
     */
    explicit Node(const T& _value) : value(_value), next(nullptr), prev(nullptr)
    {
    }
};

/**
 * @brief Iterator for traversing a doubly linked list.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T>
class ListIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;  ///< Required iterator category.
    using value_type = T;                                       ///< Type of value pointed to.
    using difference_type = std::ptrdiff_t;  ///< Type to represent the difference between two iterators.
    using pointer = T*;                      ///< Pointer type to the value type.
    using reference = T&;                    ///< Reference type to the value type.

    /**
     * @brief Construct a new ListIterator.
     *
     * @param node Pointer to the node to start the iteration.
     */
    explicit ListIterator(Node<T>* node) : mNode(node)
    {
    }

    ListIterator() = default;

    /**
     * @brief Dereference operator to get the value of the current node.
     *
     * @return Reference to the current node's value.
     */
    T& operator*()
    {
        if (!mNode || mIsFinished)
        {
            throw std::runtime_error("operator* accessing invalid iterator.");
        }
        return mNode->value;
    }

    /**
     * @brief Dereference operator to get the value of the current node (const version).
     *
     * @return Const reference to the current node's value.
     */
    const T& operator*() const
    {
        if (!mNode || mIsFinished)
        {
            throw std::runtime_error("operator* accessing invalid iterator.");
        }
        return mNode->value;
    }

    /**
     * @brief Arrow operator to access the member of the current node's value.
     *
     * @return Pointer to the current node's value.
     */
    T* operator->()
    {
        if (!mNode || mIsFinished)
        {
            throw std::runtime_error("operator-> accessing invalid iterator.");
        }
        return &mNode->value;
    }

    /**
     * @brief Arrow operator to access the member of the current node's value (const version).
     *
     * @return Const pointer to the current node's value.
     */
    const T* operator->() const
    {
        if (!mNode || mIsFinished)
        {
            throw std::runtime_error("operator-> accessing invalid iterator.");
        }
        return &mNode->value;
    }

    /**
     * @brief Prefix increment operator (move to the next node).
     *
     * @return Reference to the updated iterator.
     */
    ListIterator& operator++()
    {
        if (!mNode)
        {
            throw std::runtime_error("operator++ accessing invalid iterator.");
        }

        if (mIsFinished)
        {
            throw std::runtime_error("operator++ accessing finished iterator.");
        }

        const bool isTailNode = mNode->next == nullptr;
        if (isTailNode)
        {
            mIsFinished = true;
        }
        else
        {
            mNode = mNode->next;  // Move to the next node in the list.
        }

        return *this;
    }

    /**
     * @brief Prefix decrement operator (move to the previous node).
     *
     * @return Reference to the updated iterator.
     */
    ListIterator& operator--()
    {
        if (!mNode)
        {
            throw std::runtime_error("operator-- accessing invalid iterator.");
        }

        if (mIsFinished)
        {
            mIsFinished = false;
        }
        else
        {
            mNode = mNode->prev;  // Move to the previous node in the list.
        }

        return *this;
    }

    /**
     * @brief Postfix increment operator (move to the next node).
     *
     * @return A copy of the iterator before incrementing.
     */
    ListIterator operator++(int)
    {
        if (!mNode)
        {
            throw std::runtime_error("operator++ accessing invalid iterator.");
        }

        if (mIsFinished)
        {
            throw std::runtime_error("operator++ invalid operation on end() iterator.");
        }

        ListIterator tmp = *this;
        ++(*this);  // Move to the next node.
        return tmp;
    }

    /**
     * @brief Postfix decrement operator (move to the previous node).
     *
     * @return A copy of the iterator before decrementing.
     */
    ListIterator operator--(int)
    {
        if (!mNode)
        {
            throw std::runtime_error("operator-- accessing invalid iterator.");
        }

        ListIterator tmp = *this;
        --(*this);  // Move to the previous node.
        return tmp;
    }

    /**
     * @brief Equality comparison operator.
     *
     * @param other The iterator to compare to.
     * @return True if both iterators point to the same node, false otherwise.
     */
    bool operator==(const ListIterator& other) const
    {
        return mNode == other.mNode && mIsFinished == other.mIsFinished;
    }

    /**
     * @brief Inequality comparison operator.
     *
     * @param other The iterator to compare to.
     * @return True if both iterators do not point to the same node, false otherwise.
     */
    bool operator!=(const ListIterator& other) const
    {
        return mNode != other.mNode || mIsFinished != other.mIsFinished;
    }

    /**
     * @brief Move the iterator forward by n steps.
     *
     * @param n Number of steps to move forward.
     * @return A new iterator that is n steps ahead.
     */
    ListIterator operator+(int n)
    {
        if (n < 0)
        {
            throw std::invalid_argument("operator+ does not accept negative values. Use operator- instead.");
        }

        if (!mNode)  // If the iterator is null, throw an exception.
        {
            throw std::runtime_error("Cannot increment a null iterator.");
        }

        ListIterator tmp = *this;
        while (n-- > 0 && tmp.mNode)  // Move forward n steps, or until the end.
        {
            ++tmp;  // Move forward by one node.
        }
        return tmp;
    }

    /**
     * @brief Move the iterator backward by n steps.
     *
     * @param n Number of steps to move backward.
     * @return A new iterator that is n steps behind.
     */
    ListIterator operator-(int n)
    {
        if (n < 0)
        {
            throw std::invalid_argument("operator- does not accept negative values. Use operator+ instead.");
        }

        if (!mNode)  // If the iterator is null, throw an exception.
        {
            throw std::runtime_error("Cannot decrement a null iterator.");
        }

        ListIterator it = *this;
        while (n-- > 0 && it.mNode)
        {
            --it;  // Move backward by one node.
        }
        return it;
    }

    /**
     * @brief Calculate the distance between two iterators.
     *
     * @param other The iterator to calculate the distance to.
     * @return The number of steps between the two iterators.
     */
    int operator-(const ListIterator& other) const
    {
        ListIterator current = *this;
        ListIterator target = other;
        int distance = 0;

        // If 'this' is before 'other', move forward
        if (current <= target)
        {
            while (current != target)
            {
                ++current;
                --distance;
                if (!current.mNode)
                {
                    throw std::out_of_range("Iterator moved past the end of the list.");
                }
            }
        }
        // If 'this' is after 'other', move backward
        else
        {
            while (current != target)
            {
                --current;
                ++distance;
                if (!current.mNode)
                {
                    throw std::out_of_range("Iterator moved past the beginning of the list.");
                }
            }
        }

        return distance;
    }

    /**
     * @brief Less than or equal to comparison for iterators.
     *
     * @param other The iterator to compare to.
     * @return True if this iterator is before or equal to the other iterator.
     */
    bool operator<=(const ListIterator& other) const
    {
        return *this < other || *this == other;
    }

    /**
     * @brief Greater than or equal to comparison for iterators.
     *
     * @param other The iterator to compare to.
     * @return True if this iterator is after or equal to the other iterator.
     */
    bool operator>=(const ListIterator& other) const
    {
        return *this > other || *this == other;
    }

    /**
     * @brief Less than comparison for iterators.
     *
     * @param other The iterator to compare to.
     * @return True if this iterator is before the other iterator.
     */
    bool operator<(const ListIterator& other) const
    {
        Node<T>* node1 = mNode;
        Node<T>* node2 = other.mNode;

        while (node1)
        {
            if (node1 == node2)  // If node1 reaches node2, it means node1 is before node2.
            {
                return true;
            }
            node1 = node1->next;
        }
        return false;
    }

    /**
     * @brief Greater than comparison for iterators.
     *
     * @param other The iterator to compare to.
     * @return True if this iterator is after the other iterator.
     */
    bool operator>(const ListIterator& other) const
    {
        Node<T>* node1 = mNode;
        Node<T>* node2 = other.mNode;

        while (node2)  // Traverse node2 instead of node1
        {
            if (node2 == node1)  // If node2 reaches node1, it means node1 is after node2.
            {
                return true;
            }
            node2 = node2->next;
        }
        return false;
    }

private:
    Node<T>* mNode;           ///< Pointer to the current node.
    bool mIsFinished{false};  ///< Flag to know if we are in the end of the list.
};

/**
 * @brief Represents a doubly linked list.
 *
 * @tparam T The type of elements stored in the list.
 */
template <typename T>
class List
{
public:
    using value_type = T;
    using iterator = ListIterator<T>;

    // Destructor to release all dynamically allocated nodes.
    ~List()
    {
        // Start from the head of the list
        Node<T>* current = mHead;
        while (current != nullptr)
        {
            Node<T>* nextNode = current->next;
            delete current;      // Delete the current node
            current = nextNode;  // Move to the next node
        }
    }

    /**
     * @brief Default Constructor.
     *
     * Initializes an empty list.
     *
     * @complexity O(1) for initialization.
     * @spacecomplexity O(1) for the object itself.
     */
    List() = default;
    List(int size){};

    /**
     * @brief Constructor to initialize with an initializer list.
     *
     * Initializes the list with the elements from the given initializer list.
     *
     * @param list An initializer list to populate the list.
     *
     * @complexity O(n), where n is the number of elements in the initializer list.
     * @spacecomplexity O(n), where n is the number of elements in the initializer list.
     */
    List(std::initializer_list<T> list)
    {
        for (const auto& item : list)
        {
            append(item);  // Use the append method to add each item to the list.
        }
    }

    /**
     * @brief Copy Constructor.
     *
     * Creates a new list by copying all elements from the other list.
     *
     * @param other The list to copy from.
     *
     * @complexity O(n), where n is the number of elements in the other list.
     * @spacecomplexity O(n), where n is the number of elements in the other list.
     */
    List(const List& other)
    {
        for (const auto& item : other)
        {
            append(item);  // Copy each element from the other list.
        }
    }

    /**
     * @brief Copy Assignment Operator.
     *
     * Assigns all elements from the other list to this list.
     * If the lists are not the same, the current list is cleared first, and the elements are copied.
     *
     * @param other The list to assign from.
     * @return Reference to this list.
     *
     * @complexity O(n), where n is the number of elements in the other list. Clearing the list is O(n) as well.
     * @spacecomplexity O(n), where n is the number of elements in the other list.
     */
    List& operator=(const List& other)
    {
        if (this == &other)
        {
            return *this;  // Avoid self-assignment.
        }

        clear();  // Clear the current list.

        // Copy elements from the other list.
        for (const auto& item : other)
        {
            append(item);
        }

        return *this;
    }

    /**
     * @brief Move Constructor.
     *
     * Transfers ownership of the resources from the other list to this list.
     * The moved-from list is left in a valid but unspecified state.
     *
     * @param other The list to move from.
     *
     * @complexity O(1) for moving the resources.
     * @spacecomplexity O(1) for the new object, no additional memory allocated.
     */
    List(List&& other) noexcept : mHead(other.mHead), mTail(other.mTail), mSize(other.mSize)
    {
        // Nullify the state of the moved-from object.
        other.mHead = nullptr;
        other.mTail = nullptr;
        other.mSize = 0;
    }

    /**
     * @brief Move Assignment Operator.
     *
     * Transfers ownership of the resources from the other list to this list.
     * The moved-from list is left in a valid but unspecified state.
     *
     * @param other The list to move from.
     * @return Reference to this list.
     *
     * @complexity O(1) for moving the resources.
     * @spacecomplexity O(1) for the new object, no additional memory allocated.
     */
    List& operator=(List&& other) noexcept
    {
        if (this == &other)
        {
            return *this;  // Avoid self-assignment.
        }

        clear();  // Clear the current list.

        // Move the resources from the other list.
        mHead = other.mHead;
        mTail = other.mTail;
        mSize = other.mSize;

        // Nullify the state of the moved-from object.
        other.mHead = nullptr;
        other.mTail = nullptr;
        other.mSize = 0;

        return *this;
    }
    /**
     * @brief Access the element at the specified index.
     *
     * @param index The index of the element to access.
     * @return Reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     *
     * @complexity O(n), where n is the index. We traverse the list to find the element.
     * @spacecomplexity O(1)
     */
    T& operator[](std::size_t index)
    {
        if (index >= mSize)
        {
            throw std::out_of_range("Index out of range.");
        }

        Node<T>* currentNode = mHead;
        for (std::size_t i = 0; i < index; ++i)
        {
            currentNode = currentNode->next;
        }

        return currentNode->value;
    }

    /**
     * @brief Access the element at the specified index (const version).
     *
     * @param index The index of the element to access.
     * @return Const reference to the element at the specified index.
     * @throws std::out_of_range if the index is out of bounds.
     *
     * @complexity O(n), where n is the index. We traverse the list to find the element.
     * @spacecomplexity O(1)
     */
    const T& operator[](std::size_t index) const
    {
        if (index >= mSize)
        {
            throw std::out_of_range("Index out of range.");
        }

        Node<T>* currentNode = mHead;
        for (std::size_t i = 0; i < index; ++i)
        {
            currentNode = currentNode->next;
        }

        return currentNode->value;
    }

    /**
     * @brief Compares two List objects for equality.
     *
     * This operator checks if two List instances are equal by comparing their
     * sizes and the elements in the arrays. The arrays are considered equal if they
     * have the same size and each corresponding element is equal.
     *
     * @param other The List to compare with the current list.
     * @return True if the list are equal (same size and same elements), false otherwise.
     *
     * @throws None
     *
     * @complexity
     * - Time Complexity: O(n), where n is the size of the list (each element is compared).
     * - Space Complexity: O(1), as no additional space is used besides temporary variables.
     */
    bool operator==(const List& other) const
    {
        // First, check if the sizes are the same
        if (mSize != other.mSize)
        {
            return false;
        }

        // Then, compare each element in the array
        for (int i = 0; i < mSize; ++i)
        {
            if ((*this)[i] != other[i])
            {
                return false;
            }
        }

        // If both checks passed, the arrays are equal
        return true;
    }

    /**
     * @brief Returns an iterator pointing to the first element in the list.
     *
     * @return An iterator pointing to the first element of the list.
     *
     * @complexity O(1) for returning the iterator.
     * @spacecomplexity O(1)
     */
    ListIterator<T> begin()
    {
        return ListIterator<T>(mHead);
    }

    ListIterator<T> begin() const
    {
        return ListIterator<T>(mHead);
    }

    /**
     * @brief Returns an iterator pointing past the last element in the list.
     *
     * @return An iterator pointing past the last element of the list.
     *
     * @complexity O(1) for returning the iterator.
     * @spacecomplexity O(1)
     */
    ListIterator<T> end()
    {
        if (!mTail)
        {
            return ListIterator<T>(nullptr);
        }

        ListIterator<T> finishedNode(mTail);
        finishedNode++;
        return finishedNode;
    }

    ListIterator<T> end() const
    {
        if (!mTail)
        {
            return ListIterator<T>(nullptr);
        }

        ListIterator<T> finishedNode(mTail);
        finishedNode++;
        return finishedNode;
    }

    /**
     * @brief Append an item to the doubly linked list.
     *
     * @param item The item to append to the linked list.
     *
     * @complexity O(1) for appending a new node.
     * @spacecomplexity O(1) for allocating a new node.
     */
    void append(const T& item)
    {
        auto newNode = new Node<T>(item);

        if (mSize == 0)
        {
            mHead = newNode;
            mTail = newNode;
        }
        else
        {
            mTail->next = newNode;
            newNode->prev = mTail;
            mTail = newNode;
        }

        mHead->prev = nullptr;
        mTail->next = nullptr;
        mSize++;
    }

    /**
     * @brief Insert an item at the specified position.
     *
     * @param item The item to insert into the list.
     * @param pos The index specifying the position where the element will be inserted.
     * @param return iterator to the inserted element.
     *
     * @complexity O(n) in the worst case, since it may require traversal of the list to the insertion point.
     * @spacecomplexity O(1) for inserting a single element.
     */
    ListIterator<T> insert(const T& item, int pos)
    {
        // Check if the position is within valid bounds (0 to size inclusive).
        if (pos < 0 || pos > mSize + 1)
        {
            throw std::out_of_range("Index out of bounds in List::insert");
        }

        // Case 1: Inserting at the beginning (position 0).
        if (pos == 0)
        {
            if (mSize == 0)
            {
                append(item);
                return ListIterator<T>(mHead);
            }

            auto newNode = new Node<T>(item);
            newNode->next = mHead;
            newNode->prev = nullptr;
            mHead->prev = newNode;
            mHead = newNode;

            mSize++;
            return ListIterator<T>(mHead);
        }
        // Case 2: Inserting at the end (position mSize).
        else if (pos == mSize)
        {
            append(item);
            return ListIterator<T>(mTail);
        }
        // Case 3: Inserting in the middle (any position between 1 and mSize-1).
        else
        {
            Node<T>* nodeBeforeInsertion = mHead;
            for (int i = 0; i < pos - 1; ++i)
            {
                nodeBeforeInsertion = nodeBeforeInsertion->next;  // Traverse to the node before the insertion point.
            }

            auto newNode = new Node<T>(item);
            newNode->prev = nodeBeforeInsertion;        // The new node points back to the current node.
            newNode->next = nodeBeforeInsertion->next;  // The new node points to the next node.
            nodeBeforeInsertion->next = newNode;        // The current node points to the new node.

            mSize++;
            return ListIterator<T>(newNode);
        }
    }

    /**
     * @brief Erase the element at the specified position.
     *
     * @param position Int specifying the position to erase.
     * @param return iterator to the element next to the erased element.
     *
     * @complexity O(n) in the worst case, since it may require traversal of the list to the erase point.
     * @spacecomplexity O(1) as no additional memory is allocated; the node is deleted.
     */
    ListIterator<T> erase(int pos)
    {
        if (isEmpty())
        {
            throw std::out_of_range("The list is empty in List::erase");
        }

        if (pos < 0 || pos >= mSize)
        {
            throw std::out_of_range("Index out of bounds in List::erase");
        }

        // Case 1: Erasing at the beginning (position 0).
        if (pos == 0)
        {
            if (mSize == 1)  // If there's only one element, the list will be empty after the erase.
            {
                mHead = nullptr;
                mTail = nullptr;
                mSize--;
                return ListIterator<T>(nullptr);
            }
            else  // More than one element
            {
                auto newHead = mHead->next;
                newHead->prev = nullptr;
                mHead = newHead;
                mSize--;
                return ListIterator<T>(mHead);
            }
        }
        // Case 2: Erasing the last element (position mSize - 1).
        else if (pos == mSize - 1)
        {
            if (mSize == 1)  // If there's only one element, the list will be empty after the erase.
            {
                mHead = nullptr;
                mTail = nullptr;
                mSize--;
                return ListIterator<T>(nullptr);
            }
            else  // More than one element.
            {
                // Move mTail to the previous node.
                mTail = mTail->prev;
                mTail->next = nullptr;
                mSize--;

                return end();
            }
        }
        // Case 3: Erasing in the middle (any position between 1 and mSize-1).
        else
        {
            // Traverse to the node just before the position to be erased.
            Node<T>* previousNodeToNodeToBeErased = mHead;
            for (int i = 0; i < pos - 1; ++i)
            {
                previousNodeToNodeToBeErased = previousNodeToNodeToBeErased->next;  // Move to the next node
            }

            auto nodeToBeErased = previousNodeToNodeToBeErased->next;
            auto nodeNextToNodeToBeErased = nodeToBeErased->next;

            nodeNextToNodeToBeErased->prev = previousNodeToNodeToBeErased;
            previousNodeToNodeToBeErased->next = nodeNextToNodeToBeErased;
            mSize--;

            return ListIterator<T>(nodeNextToNodeToBeErased);
        }
    }

    /**
     * @brief Get the size of the linked list (dynamic size).
     *
     * @return The total number of elements inside the list.
     *
     * @complexity O(1)
     * @spacecomplexity O(1)
     */
    [[nodiscard]] int getSize() const noexcept
    {
        return mSize;
    }

    /**
     * @brief Checks if the list has no elements.
     *
     * @return True if the list is empty, false otherwise.
     *
     * @complexity O(1)
     * @spacecomplexity O(1)
     */
    [[nodiscard]] bool isEmpty() const noexcept
    {
        return mSize == 0;
    }

    /**
     * @brief Clear the list.
     *
     * Deallocates all nodes in the list, leaving the list empty.
     *
     * @complexity O(n), where n is the number of elements in the list.
     * @spacecomplexity O(1), as no extra space is used for clearing the list.
     */
    void clear()
    {
        mHead = nullptr;
        mTail = nullptr;
        mSize = 0;
    }

private:
    Node<T>* mHead{nullptr};  ///< Pointer to the head (first) node of the linked list.
    Node<T>* mTail{nullptr};  ///< Pointer to the tail (last) node of the linked list.
    std::size_t mSize{0};     ///< The size of the linked list (number of nodes).
};
