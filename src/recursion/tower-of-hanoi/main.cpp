#include "benchmarking.hpp"

#include <algorithm>
#include <array>
#include <iostream>

// Number of disks
constexpr int nDisks = 15;

// Towers as an array of arrays
std::array<std::array<int, nDisks>, 3> towers = {};

// Function to print the current state of the towers
void printTowers()
{
    // Print the towers vertically, largest to smallest
    for (int i = nDisks - 1; i >= 0; --i)
    {
        for (int t = 0; t < 3; ++t)
        {
            std::cout << "   " << towers[t][i];
            std::cout << "\t";
        }
        std::cout << "\n";
    }

    // Print the tower labels
    std::cout << "Tower 1\tTower 2\tTower 3\n";
}

// Move a single disk from 'from' tower to 'to' tower using 'auxiliary' tower.
// Time Complexity Analysis:
// This function uses `std::count` to count the number of disks in the 'from' and 'to' towers.
// `std::count` scans the entire tower array, which takes O(n) time where 'n' is the number of disks.
// So the time complexity of this function is O(n).
void move_1_disk(int from, int auxiliary, int to)
{
    // Count the number of disks in the 'from' and 'to' towers.
    // std::count checks each element of the tower array, which takes O(n) time.
    int amountOfDisksInFrom = nDisks - std::count(towers[from].begin(), towers[from].end(), 0);
    int amountOfDisksInTo = nDisks - std::count(towers[to].begin(), towers[to].end(), 0);

    if (amountOfDisksInFrom == 0)
    {
        std::cout << "From tower doesn't have any disk." << std::endl;
        return;
    }

    // Find the index of the top disk in 'from' and the first available index in 'to'.
    int indexFrom = amountOfDisksInFrom - 1;
    int indexTo = amountOfDisksInTo;

    // Move the disk from 'from' tower to 'to' tower
    towers[to][indexTo] = towers[from][indexFrom];
    towers[from][indexFrom] = 0;  // Set the 'from' tower slot to 0, indicating the disk is moved.
}

// Recursive function to solve the Tower of Hanoi problem.
// Time Complexity Analysis:
// The recursive function `solve_with_recursion` performs two recursive calls for moving n-1 disks,
// and at each step, it calls `move_1_disk` to move a single disk, which has O(n) time complexity.
// The recurrence relation for this function is:
// T(n) = 2 * T(n - 1) + O(n)
// This implies an exponential time complexity, specifically O(2^n * n),
// because we have 2 recursive calls for n-1 disks, and for each level of recursion, we do O(n) work (moving a disk).
// The space complexity of this function is O(n), due to the depth of recursion (which is at most n).
void solve_with_recursion(int n, int from, int auxiliary, int to)
{
    if (n > 1)
    {
        // Move n-1 disks from 'from' to 'auxiliary' using 'to' as auxiliary
        solve_with_recursion(n - 1, from, to, auxiliary);

        // Move 1 disk from 'from' to 'to'
        move_1_disk(from, auxiliary, to);  // Time Complexity of this call: O(n)

        // Move n-1 disks from 'auxiliary' to 'to' using 'from' as auxiliary
        solve_with_recursion(n - 1, auxiliary, from, to);
    }
    else if (n == 1)
    {
        // Base case: move 1 disk from 'from' to 'to'
        move_1_disk(from, auxiliary, to);  // Time Complexity of this call: O(n)
    }
}

/*
Time Complexity Summary:

1. `move_1_disk`: O(n) due to `std::count` iterating through the tower array to count the disks.
2. `solve_with_recursion`:
    - The recurrence relation for the time complexity of the recursive function is:
        T(n) = 2T(n-1) + O(n)
    - Expanding the recurrence, we get a time complexity of O(2^n * n), which accounts for:
        - Exponential growth in the number of recursive calls (2 recursive calls per level).
        - Linear work done at each level (moving disks via `move_1_disk` which is O(n)).
    - The recursion depth is O(n), and at each level, we do O(n) work due to the `move_1_disk` function.
3. Space Complexity: O(n) due to the recursion depth (recursive calls stack).
    - The function does not use any additional data structures that would increase space complexity.

Example:
- For n = 3 disks, we have the following recursive breakdown:
  - T(3) = 2 * T(2) + O(3)
  - T(2) = 2 * T(1) + O(2)
  - T(1) = O(1)
  - Expanding this recurrence, the total time complexity is O(2^3 * 3) = O(24) operations.

Final time complexity: O(2^n * n)
Final space complexity: O(n)

*/
// Time complexity?
// Each call will make two calls until n == 1.

int main()
{
    // Fill Tower 1 with n, n-1, ... , 2, 1.
    std::generate(towers[0].begin(), towers[0].end(), [i = nDisks]() mutable { return i--; });
    std::fill(towers[1].begin(), towers[1].end(), 0);
    std::fill(towers[2].begin(), towers[2].end(), 0);

    // Print initial state of towers:
    std::cout << "Initial state:" << std::endl;
    printTowers();

    solve_with_recursion(nDisks, 0, 1, 2);

    // Print final state of towers:
    std::cout << "Final state:" << std::endl;
    printTowers();

    return 0;
}