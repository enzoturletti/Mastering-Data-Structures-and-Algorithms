# topics/recursion/sum-natural-numbers/CMakeLists.txt

# Include the header files directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Automatically find all .cpp files in the src directory
file(GLOB SUM_NATURAL_NUMBERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add the executable with all source files
add_executable(SumNaturalNumbers main.cpp ${SUM_NATURAL_NUMBERS})

# Link the benchmarking library
target_link_libraries(SumNaturalNumbers PRIVATE benchmarking)

# Include directories for benchmarking
target_include_directories(SumNaturalNumbers PRIVATE ${CMAKE_SOURCE_DIR}/benchmark)

#Set output
set_target_properties(SumNaturalNumbers PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/recursion/)