# Define Executable Target ---
add_executable(connection_pool main.cpp)

# Target Include Directories ---
target_include_directories(connection_pool PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)