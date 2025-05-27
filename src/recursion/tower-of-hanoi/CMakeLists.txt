# topics/recursion/tower-of-hanoi/CMakeLists.txt

# Include the header files directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Automatically find all .cpp files in the src directory
file(GLOB TOWER_OF_HANOI ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add the executable with all source files
add_executable(TowerOfHanoi main.cpp ${TOWER_OF_HANOI})

# Link the benchmarking library
target_link_libraries(TowerOfHanoi PRIVATE benchmarking)

# Include directories for benchmarking
target_include_directories(TowerOfHanoi PRIVATE ${CMAKE_SOURCE_DIR}/benchmark)

#Set output
set_target_properties(TowerOfHanoi PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/recursion/)