# Root CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(MasteringDataStructuresAndAlgorithms)

# Enable testing
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Check for compiler compatibility with C++20
if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "10")
    message(FATAL_ERROR "The compiler must support C++20. Please use GCC 10 or later, Clang 10 or later, or MSVC 2019 (16.10) or later.")
endif()

add_subdirectory(benchmark)
add_subdirectory(src)
add_subdirectory(tests)

