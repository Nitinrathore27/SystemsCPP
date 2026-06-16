# Define the Test Executable ---
add_executable(connection_pool_test connection_pool_test.cpp)

# Include Directories ---
target_include_directories(connection_pool_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link GoogleTest ---
target_link_libraries(connection_pool_test PRIVATE gtest gtest_main)

# Discover Tests ---
include(GoogleTest)
gtest_discover_tests(connection_pool_test)