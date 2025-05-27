#include <benchmarking.hpp>
#include <chrono>
#include <iostream>

// Recursive Taylor series implementation
double e_taylor_recursive(double x, double n)
{
    static double p = 1, f = 1;

    if (n == 0)
    {
        return 1;
    }

    double result = e_taylor_recursive(x, n - 1);
    p = p * x;
    f = f * n;
    return result + p / f;
}

// Iterative Taylor series implementation
double e_taylor_iterative(double x, double n)
{
    double result = 1;  // Initial term (1 for n=0)
    double p = 1;       // x^0 = 1
    double f = 1;       // 0! = 1

    for (double i = 1; i <= n; i++)
    {
        p = p * x;                // Compute x^i
        f = f * i;                // Compute i!
        result = result + p / f;  // Add the term to the result
    }
    return result;
}

// Iterative Taylor series implementation optimized
double e_taylor_iterative_optimized(double x, double n)
{
    double result = 1;
    for (; n > 0; n--)
    {
        result = 1 + (x / n) * result;
    }
    return result;
}

// Recursive Taylor series implementation optimized
double e_taylor_recursion_optimized(double x, double n)
{
    static double S = 1;

    if (n == 0)
    {
        return S;
    }

    S = 1 + (x / n) * S;

    return e_taylor_recursion_optimized(x, n - 1);
}

int main()
{
    const double x = 5;   // Value for x in e^x
    const double n = 15;  // Number of terms in the Taylor series

    benchmark_function("Recursive Taylor", e_taylor_recursive, x, n);
    benchmark_function("Recursive Taylor optimized", e_taylor_recursion_optimized, x, n);
    benchmark_function("Iterative Taylor", e_taylor_iterative, x, n);
    benchmark_function("Iterative Taylor optimized", e_taylor_iterative_optimized, x, n);

    return 0;
}
