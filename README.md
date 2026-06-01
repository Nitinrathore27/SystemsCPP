# Thread-Safe LRU Cache

A high-performance, thread-safe Least Recently Used (LRU) Cache implemented in native C++ using STL containers. This project demonstrates synchronization patterns, focusing on thread safety under concurrent read and write operations.

## 🚀 Features
- **$O(1)$ Operations:** Fast lookups, insertions, and evictions using `std::unordered_map` and `std::list`.
- **Thread Safety:** Implemented using modern C++ concurrency primitives (`std::mutex`, `std::unique_lock`).
- **Header-Only / Easy Integration:** Designed as a generic template class supporting arbitrary key-value types.

## 🛠️ Architecture & Technical Decisions
- **Data Structures:** - `std::list<std::pair<Key, Value>>` to track elements from Most Recently Used (front) to Least Recently Used (back).
  - `std::unordered_map<Key, typename std::list<...>::iterator>` for constant-time lookups to elements inside the linked list.
- **Concurrency Strategy:** - *Current Status:* Uses a global lock (`std::mutex`) with `std::unique_lock` to ensure strict mutual exclusion across both `get()` and `put()` operations.
  - *Note on Readers-Writer Optimization:* Because a standard LRU `get()` operation modifies the internal ordering of the linked list (moving the accessed element to the front), a simple `std::shared_lock` (read-lock) is insufficient on its own without data races. Future iterations may explore cache sharding/segmentation or deferred list updates to optimize read throughput.

## 📋 Requirements
- C++14 (or higher) compliant compiler (e.g., GCC, Clang, MSVC)
- CMake (version 3.10 or higher)

## 🔧 Building and Running

### Build Instructions
```bash
mkdir build && cd build
cmake ..
cmake --build .
