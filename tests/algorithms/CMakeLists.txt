enable_testing()
find_package(GTest REQUIRED)

# Search algorithms tests
add_executable(SearchAlgorithmsTests search-algorithms-tests.cpp)
target_include_directories(SearchAlgorithmsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(SearchAlgorithmsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(SearchAlgorithmsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Max element tests
add_executable(MaxElementTests max-element-tests.cpp)
target_include_directories(MaxElementTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(MaxElementTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(MaxElementTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Reverse elements tests
add_executable(ReverseElementsTests reverse-elements-tests.cpp)
target_include_directories(ReverseElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(ReverseElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(ReverseElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Shift elements tests
add_executable(ShiftElementsTests shift-elements-tests.cpp)
target_include_directories(ShiftElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(ShiftElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(ShiftElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Rotate elements tests
add_executable(RotateElementsTests rotate-elements-tests.cpp)
target_include_directories(RotateElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(RotateElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(RotateElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# isSorted tests
add_executable(IsSortedTests is-sorted-tests.cpp)
target_include_directories(IsSortedTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(IsSortedTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(IsSortedTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Merge elements tests
add_executable(MergeElementsTests merge-elements-tests.cpp)
target_include_directories(MergeElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(MergeElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(MergeElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Union elements tests
add_executable(UnionElementsTests union-elements-tests.cpp)
target_include_directories(UnionElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(UnionElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(UnionElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Intersection elements tests
add_executable(IntersectionElementsTests intersection-elements-tests.cpp)
target_include_directories(IntersectionElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(IntersectionElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(IntersectionElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Difference elements tests
add_executable(DifferenceElementsTests difference-elements-tests.cpp)
target_include_directories(DifferenceElementsTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(DifferenceElementsTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(DifferenceElementsTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Delete duplicates elements tests
add_executable(DeleteDuplicatesTests delete-duplicates-tests.cpp)
target_include_directories(DeleteDuplicatesTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(DeleteDuplicatesTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(DeleteDuplicatesTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Permutation tests
add_executable(PermutationTests permutation-tests.cpp)
target_include_directories(PermutationTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(PermutationTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(PermutationTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Combination tests
add_executable(CombinationTests combination-tests.cpp)
target_include_directories(CombinationTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(CombinationTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(CombinationTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Parentheses matching tests
add_executable(ParenthesesMatchingTests parentheses-matching-tests.cpp)
target_include_directories(ParenthesesMatchingTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(ParenthesesMatchingTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(ParenthesesMatchingTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# BubbleSort tests
add_executable(SortingTests sorting-tests.cpp)
target_include_directories(SortingTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(SortingTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(SortingTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Divide and conquer tests
add_executable(DivideAndConquerTests divide-and-conquer-tests.cpp)
target_include_directories(DivideAndConquerTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(DivideAndConquerTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(DivideAndConquerTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# OptimizationProblems Greedy Method tests
add_executable(OptimizationProblemsGMTests optimization-problems-gm-tests.cpp)
target_include_directories(OptimizationProblemsGMTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(OptimizationProblemsGMTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(OptimizationProblemsGMTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# OptimizationProblems Dynamic Programming tests
add_executable(OptimizationProblemsDPTests optimization-problems-dp-tests.cpp)
target_include_directories(OptimizationProblemsDPTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(OptimizationProblemsDPTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(OptimizationProblemsDPTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Backtracking Programming tests
add_executable(BacktrackingTests backtracking-tests.cpp)
target_include_directories(BacktrackingTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(BacktrackingTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(BacktrackingTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/algorithms/)

# Register each set of tests
add_test(NAME SearchAlgorithmsTestWithInt COMMAND SearchAlgorithmsTests)
add_test(NAME SearchAlgorithmsTestWithString COMMAND SearchAlgorithmsTests)

add_test(NAME MaxElementAlgorithmsTestWithInt COMMAND MaxElementTests)
add_test(NAME MaxElementStaticArrayInt COMMAND MaxElementTests)
add_test(NAME MaxElementAlgorithmsTestWithString COMMAND MaxElementTests)
add_test(NAME MaxElementStaticArrayString COMMAND MaxElementTests)

add_test(NAME ReverseAlgorithmsTestWithInt COMMAND ReverseElementsTests)
add_test(NAME ReverseStaticArrayInt COMMAND ReverseElementsTests)
add_test(NAME ReverseAlgorithmsTestWithString COMMAND ReverseElementsTests)
add_test(NAME ReverseStaticArrayString COMMAND ReverseElementsTests)

add_test(NAME ShiftAlgorithmsTestWithInt COMMAND ShiftElementsTests)
add_test(NAME LeftShiftElementsTestStaticArray COMMAND ShiftElementsTests)
add_test(NAME RightShiftElementsTestStaticArray COMMAND ShiftElementsTests)

add_test(NAME RotateAlgorithmsTestWithInt COMMAND RotateElementsTests)
add_test(NAME RotateAlgorithmsTestWithString COMMAND RotateElementsTests)

add_test(NAME IsSortedAlgorithmsTestWithInt COMMAND IsSortedTests)
add_test(NAME IsSortedStaticArrayInt COMMAND IsSortedTests)
add_test(NAME IsSortedAlgorithmsTestWithString COMMAND IsSortedTests)
add_test(NAME IsSortedStaticArrayString COMMAND IsSortedTests)

add_test(NAME MergeAlgorithmsTestWithInt COMMAND MergeElementsTests)
add_test(NAME MergeElementsStaticArrayInt COMMAND MergeElementsTests)
add_test(NAME MergeAlgorithmsTestWithString COMMAND MergeElementsTests)
add_test(NAME MergeElementsStaticArrayString COMMAND MergeElementsTests)

add_test(NAME UnionAlgorithmsTestWithInt COMMAND UnionElementsTests)
add_test(NAME UnionAlgorithmsTestWithString COMMAND UnionElementsTests)

add_test(NAME IntersectionAlgorithmsTestWithInt COMMAND IntersectionElementsTests)
add_test(NAME IntersectionAlgorithmsTestWithString COMMAND IntersectionElementsTests)

add_test(NAME DifferenceAlgorithmsTestWithInt COMMAND DifferenceElementsTests)
add_test(NAME DifferenceAlgorithmsTestWithString COMMAND DifferenceElementsTests)

add_test(NAME DeleteDuplicatesTestWithInt COMMAND DifferenceElementsTests)
add_test(NAME DeleteDuplicatesTestWithString COMMAND DifferenceElementsTests)

add_test(NAME PermutationTests COMMAND PermutationTests)
add_test(NAME CombinationTests COMMAND CombinationTests)

add_test(NAME ParenthesesMatchTest COMMAND ParenthesesMatchingTests)

add_test(NAME SortingElementsTests COMMAND SortingTests)

add_test(NAME DivideAndConquerTest COMMAND DivideAndConquerTests)

add_test(NAME OptimizationGMProblemsTest COMMAND OptimizationProblemsGMTests)
add_test(NAME OptimizationDPProblemsTest COMMAND OptimizationProblemsDPTests)

add_test(NAME BacktrackingTest COMMAND BacktrackingTests)

