# Define Executable Target ---
add_executable(lru_cache main.cpp)

# Target Include Directories ---
target_include_directories(lru_cache PRIVATE ${CMAKE_SOURCE_DIR}/include)