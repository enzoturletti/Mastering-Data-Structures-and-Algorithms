# topics/recursion/pow/CMakeLists.txt

# Include the header files directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Automatically find all .cpp files in the src directory
file(GLOB POW ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Add the executable with all source files
add_executable(Pow main.cpp ${POW})

# Link the benchmarking library
target_link_libraries(Pow PRIVATE benchmarking)

# Include directories for benchmarking
target_include_directories(Pow PRIVATE ${CMAKE_SOURCE_DIR}/benchmark)

#Set output
set_target_properties(Pow PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/recursion/)