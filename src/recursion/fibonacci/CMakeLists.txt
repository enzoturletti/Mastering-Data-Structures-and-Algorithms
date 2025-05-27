# topics/recursion/pow/CMakeLists.txt

# Include the header files directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Automatically find all .cpp files in the src directory
file(GLOB FIBONACCI ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add the executable with all source files
add_executable(Fibonacci main.cpp ${FIBONACCI})

# Link the benchmarking library
target_link_libraries(Fibonacci PRIVATE benchmarking)

# Include directories for benchmarking
target_include_directories(Fibonacci PRIVATE ${CMAKE_SOURCE_DIR}/benchmark)

#Set output
set_target_properties(Fibonacci PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/recursion/)