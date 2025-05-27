#include <benchmarking.hpp>

int fact_with_recursion(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return fact_with_recursion(n - 1) * n;
    }
}

int fact_with_iteration(int n)
{
    int F = 1;
    for (int i = 1; i <= n; i++)
    {
        F = F * i;
    }
    return F;
}

int combination_with_fact_iteration(int n, int r)
{
    int t0 = fact_with_iteration(n);
    int t1 = fact_with_iteration(r);
    int t2 = fact_with_iteration(n - r);
    return t0 / (t1 * t2);
}

int combination_with_fact_recursion(int n, int r)
{
    int t0 = fact_with_recursion(n);
    int t1 = fact_with_recursion(r);
    int t2 = fact_with_recursion(n - r);
    return t0 / (t1 * t2);
}

int combination_with_pascal_three(int n, int r)
{
    if (r == 0 || n == r)
    {
        return 1;
    }
    return combination_with_pascal_three(n - 1, r - 1) + combination_with_pascal_three(n - 1, r);
}

int main()
{
    const double n = 11;
    const double r = 5;

    benchmark_function("combination_with_fact_iteration: ", combination_with_fact_iteration, n, r);
    benchmark_function("combination_with_fact_recursion: ", combination_with_fact_recursion, n, r);
    benchmark_function("combination_with_pascal_three: ", combination_with_pascal_three, n, r);

    return 0;
}
