enable_testing()
find_package(GTest REQUIRED)

# 1- Student challenges tests
add_executable(StudentChallenges1 1.finding-missing-element-tests.cpp)
target_include_directories(StudentChallenges1 PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures ${CMAKE_SOURCE_DIR}/src/student-challenges)
target_link_libraries(StudentChallenges1 algorithms data-structures student-challenges GTest::GTest GTest::Main)
set_target_properties(StudentChallenges1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/student-challenges/)

# 2- Student challenges tests
add_executable(StudentChallenges2 2.finding-duplicate-elements-tests.cpp)
target_include_directories(StudentChallenges2 PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures ${CMAKE_SOURCE_DIR}/src/student-challenges)
target_link_libraries(StudentChallenges2 algorithms data-structures student-challenges GTest::GTest GTest::Main)
set_target_properties(StudentChallenges2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/student-challenges/)

# 3- Student challenges tests
add_executable(StudentChallenges3 3.finding-pair-with-sum-k-tests.cpp)
target_include_directories(StudentChallenges3 PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures ${CMAKE_SOURCE_DIR}/src/student-challenges)
target_link_libraries(StudentChallenges3 algorithms data-structures student-challenges GTest::GTest GTest::Main)
set_target_properties(StudentChallenges3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/student-challenges/)


# Register each set of tests
add_test(NAME FindingMissingElementInSortedDynamicArray COMMAND StudentChallenges1)
add_test(NAME FindingMultipleMissingElementInSortedDynamicArray COMMAND StudentChallenges1)
add_test(NAME FindingMultipleMissingElementInDynamicArray COMMAND StudentChallenges1)
add_test(NAME FindingDuplicateElementsInDynamicArray COMMAND StudentChallenges2)
add_test(NAME FindingPairWithSumKInDynamicArray COMMAND StudentChallenges3)

