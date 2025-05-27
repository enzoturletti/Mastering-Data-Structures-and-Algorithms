#include <chrono>
#include <iostream>
#include "benchmarking.hpp"  // Include the benchmarking header

// Recursive Power Option 1: Simple Recursion
int recursive_pow_option_1(int m, int n)
{
    if (n == 0)
    {
        return 1;
    }

    return recursive_pow_option_1(m, n - 1) * m;
}

// Recursive Power Option 2: Exponentiation by Squaring (Optimized)
int recursive_pow_option_2(int m, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n % 2 == 0)  // Is Even
    {
        return recursive_pow_option_2(m * m, n / 2);
    }
    else
    {
        return m * recursive_pow_option_2(m * m, (n - 1) / 2);
    }
}

// For-Loop Power Option 1: Simple For-Loop
int for_pow_option_1(int m, int n)
{
    int result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= m;  // Multiply by m
    }

    return result;
}

// For-Loop Power Option 2: Exponentiation by Squaring (Optimized)
int for_pow_option_2(int m, int n)
{
    int result = 1;
    while (n > 0)
    {
        if (n % 2 == 1)
        {
            result *= m;
        }
        m *= m;
        n /= 2;
    }

    return result;
}

int main()
{
    int m = 2;
    int n = 20;  // Change n as needed for testing

    benchmark_function("recursive_pow_option_1", recursive_pow_option_1, m, n);
    benchmark_function("recursive_pow_option_2", recursive_pow_option_2, m, n);
    benchmark_function("for_pow_option_1", for_pow_option_1, m, n);
    benchmark_function("for_pow_option_2", for_pow_option_2, m, n);

    return 0;
}
