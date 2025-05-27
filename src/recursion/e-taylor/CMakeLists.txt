# topics/recursion/e-taylor/CMakeLists.txt

# Include the header files directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Automatically find all .cpp files in the src directory
file(GLOB E_TAYLOR ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add the executable with all source files
add_executable(ETaylor main.cpp ${E_TAYLOR})

# Link the benchmarking library
target_link_libraries(ETaylor PRIVATE benchmarking)

# Include directories for benchmarking
target_include_directories(ETaylor PRIVATE ${CMAKE_SOURCE_DIR}/benchmark)

#Set output
set_target_properties(ETaylor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/recursion/)