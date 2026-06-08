cmake_minimum_required(VERSION 3.20)
project(CppSystemDesignPortfolio LANGUAGES CXX)

# C++ Standard Configuration ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler Warnings ---
add_compile_options(-Wall -Wextra -pedantic -Wconversion)

# Feature Detection (C++20/23) ---
include(CheckCXXSourceCompiles)
set(CMAKE_REQUIRED_FLAGS "-std=c++20")
check_cxx_source_compiles("
    #include <thread>
    int main() { std::jthread t; return 0; }
" HAS_CXX20_JTHREAD)
set(CMAKE_REQUIRED_FLAGS "")

if(HAS_CXX20_JTHREAD)
    message(STATUS "Feature check passed: std::jthread is supported!")
endif()

# Download and Integrate GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# Ensure cross-platform compatibility (especially for MSVC)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable Testing ---
enable_testing()

# Monorepo Subdirectories ---
add_subdirectory(projects/lru-cache)
add_subdirectory(projects/connection-pool)