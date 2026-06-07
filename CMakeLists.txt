cmake_minimum_required(VERSION 3.20)

project(threadsafe-lru LANGUAGES CXX)

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

# Include Directories ---
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable Testing ---
enable_testing()

# Subdirectories ---
add_subdirectory(src)
add_subdirectory(test)