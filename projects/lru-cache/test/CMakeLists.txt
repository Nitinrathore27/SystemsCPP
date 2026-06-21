# Define the Test Executable ---
add_executable(lru_cache_test lru_cache_test.cpp)

# Include Directories ---
target_include_directories(lru_cache_test PRIVATE ${CMAKE_SOURCE_DIR}/../include)

# Link GoogleTest ---
target_link_libraries(lru_cache_test PRIVATE gtest gtest_main)

# Discover Tests ---
include(GoogleTest)
gtest_discover_tests(lru_cache_test)