#include <iostream>
#include <memory>
#include <vector>
#include "benchmarking.hpp"  // Include the benchmarking header

int fib_with_recursion(int n)
{
    if (n <= 1)
    {
        return n;
    }

    return fib_with_recursion(n - 1) + fib_with_recursion(n - 2);
}

static constexpr int MAX_VALUE_ALLOWED = 101;
static std::array<int, MAX_VALUE_ALLOWED> saved_values = {-1};
int fib_with_recursion_memorization(int n)
{
    if (n > 100)
    {
        std::cout << "Maximum n allowed is 100." << std::endl;
        return -1;
    }

    if (n <= 1)
    {
        if (saved_values[n] == -1)
        {
            saved_values[n] = n;  // Store Fibonacci value for base case
        }
        return saved_values[n];
    }

    if (saved_values[n] == -1)
    {
        if (saved_values[n - 1] == -1)
        {
            saved_values[n - 1] = fib_with_recursion_memorization(n - 1);
        }
        if (saved_values[n - 2] == -1)
        {
            saved_values[n - 2] = fib_with_recursion_memorization(n - 2);
        }
        saved_values[n] = saved_values[n - 1] + saved_values[n - 2];
    }

    return saved_values[n];
}

int fib_with_iteration(int n)
{
    if (n <= 1)
        return n;
    int t0 = 0;
    int t1 = 1;
    int result = 0;

    for (int i = 2; i <= n; i++)
    {
        result = t0 + t1;
        t0 = t1;
        t1 = result;
    }
    return result;
}

int main()
{
    const double n = 10;

    benchmark_function("Fibonacci with recursion", fib_with_recursion, n);
    benchmark_function("Fibonacci with iteration", fib_with_iteration, n);
    benchmark_function("Fibonacci with recursion and memorization", fib_with_recursion_memorization, n);

    return 0;
}
