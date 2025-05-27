#pragma once

#include <chrono>
#include <functional>
#include <iostream>

// Generic benchmark function with variadic templates
template <typename Func, typename... Args>
void benchmark_function(const std::string& function_name, Func&& func, Args&&... args)
{
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Call the passed function with the unpacked arguments
    int result = std::forward<Func>(func)(std::forward<Args>(args)...);

    // End the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the time taken
    std::chrono::duration<double> elapsed = end - start;

    // Output the results
    std::cout << function_name << " result: " << result << ", Time: " << elapsed.count() << " seconds\n";
}
