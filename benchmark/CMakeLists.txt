# benchmarking/CMakeLists.txt

# Create a library from benchmarking.hpp
add_library(benchmarking INTERFACE)

# Specify include directories for the benchmarking library
target_include_directories(benchmarking INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
