# tests/data-structures/CMakeLists.txt

enable_testing()
find_package(GTest REQUIRED)

# Add separate test executables for each test suite

# Static array tests
add_executable(StaticArrayTests static-array-tests.cpp)
target_include_directories(StaticArrayTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(StaticArrayTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(StaticArrayTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

# Dynamic array tests
add_executable(DynamicArrayTests dynamic-array-tests.cpp)
target_include_directories(DynamicArrayTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(DynamicArrayTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(DynamicArrayTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

# List tests
add_executable(ListTests list-tests.cpp)
target_include_directories(ListTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(ListTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(ListTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

# Stack tests
add_executable(StackTests stack-tests.cpp)
target_include_directories(StackTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(StackTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(StackTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

# Queue tests
add_executable(QueueTests queue-tests.cpp)
target_include_directories(QueueTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(QueueTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(QueueTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

# Graph representation tests
add_executable(GraphRepresentationTests graph-representation-tests.cpp)
target_include_directories(GraphRepresentationTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(GraphRepresentationTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(GraphRepresentationTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

# Diagonal matrix tests
add_executable(DiagonalMatrixTests diagonal-matrix-tests.cpp)
target_include_directories(DiagonalMatrixTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(DiagonalMatrixTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(DiagonalMatrixTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## Lower triangule matrix tests
add_executable(LowerTriangleMatrixTests lower-triangular-matrix-tests.cpp)
target_include_directories(LowerTriangleMatrixTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(LowerTriangleMatrixTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(LowerTriangleMatrixTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## Symmetric matrix tests
add_executable(SymmetricMatrixTests symmetric-matrix-tests.cpp)
target_include_directories(SymmetricMatrixTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(SymmetricMatrixTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(SymmetricMatrixTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## Sparse matrix tests
add_executable(SparseMatrixTests sparse-matrix-tests.cpp)
target_include_directories(SparseMatrixTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(SparseMatrixTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(SparseMatrixTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## BinaryTree tests
add_executable(BinaryTreeTests binary-tree-tests.cpp)
target_include_directories(BinaryTreeTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(BinaryTreeTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(BinaryTreeTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## BinarySearchTree tests
add_executable(BinarySearchTreeTests binary-search-tree-tests.cpp)
target_include_directories(BinarySearchTreeTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(BinarySearchTreeTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(BinarySearchTreeTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## AVLTree tests
add_executable(AVLTreeTests avl-binary-search-tree-tests.cpp)
target_include_directories(AVLTreeTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(AVLTreeTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(AVLTreeTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## RedBlackTree tests
add_executable(RBTreeTests rb-binary-search-tree-tests.cpp)
target_include_directories(RBTreeTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(RBTreeTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(RBTreeTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## Heap tests
add_executable(HeapTests heap-tests.cpp)
target_include_directories(HeapTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(HeapTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(HeapTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)

## UnorderedMap tests
add_executable(UnorderedMapTests unordered-map-tests.cpp)
target_include_directories(UnorderedMapTests PRIVATE ${CMAKE_SOURCE_DIR}/src/algorithms ${CMAKE_SOURCE_DIR}/src/data-structures)
target_link_libraries(UnorderedMapTests algorithms data-structures GTest::GTest GTest::Main)
set_target_properties(UnorderedMapTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/data-structures/)


# Register each set of tests
add_test(NAME StaticArrayTest COMMAND StaticArrayTests)
add_test(NAME DynamicArrayTest COMMAND DynamicArrayTests)
add_test(NAME ListTest COMMAND ListTests)
add_test(NAME StackTest COMMAND StackTests)
add_test(NAME QueueTest COMMAND QueueTests)
add_test(NAME GraphRepresentationTest COMMAND GraphRepresentationTests)
add_test(NAME DiagonalMatrixTest COMMAND DiagonalMatrixTests)
add_test(NAME LowerTriangularMatrixTest COMMAND LowerTriangleMatrixTests)
add_test(NAME SymmetricMatrixTest COMMAND SymmetricMatrixTests)
add_test(NAME SparseMatrix COMMAND SparseMatrixTests)
add_test(NAME BinaryTreeTest COMMAND BinaryTreeTests)
add_test(NAME BinarySearchTreeTest COMMAND BinarySearchTreeTests)
add_test(NAME AVLTreeTest COMMAND AVLTreeTests)
add_test(NAME RBTreeTest COMMAND RBTreeTests)
add_test(NAME HeapTest COMMAND HeapTests)
add_test(NAME UnorderedMapTest COMMAND UnorderedMapTests)
