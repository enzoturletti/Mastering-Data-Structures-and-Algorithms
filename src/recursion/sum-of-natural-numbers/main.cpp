#include <chrono>
#include <iostream>
#include "benchmarking.hpp"

// Recursive implementation
int sum_n_recursive(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return sum_n_recursive(n - 1) + n;
    }
}

// Loop-based implementation
int sum_n_with_loop(int n)
{
    int S = 0;
    for (int i = 1; i <= n; i++)
    {
        S = S + i;
    }
    return S;
}

// Direct formula implementation
int sum_n(int n)
{
    return (n + 1) * (n / 2) + (n % 2 == 1 ? (n / 2 + 1) : 0);  // Correct for odd n
}

int main()
{
    const int n = 100000;  // Change this value for testing different input sizes

    benchmark_function("sum_n_recursive", sum_n_recursive, n);
    benchmark_function("sum_n_with_loop", sum_n_with_loop, n);
    benchmark_function("sum_n", sum_n, n);

    return 0;
}