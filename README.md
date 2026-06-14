# Advanced Concurrent Systems in C++

Welcome to my repository dedicated to low-level system design and high-performance concurrent components in Modern C++. This repository serves as a portfolio of production-grade, thread-safe data structures and resource management utilities designed for low-latency systems.

## 🛠️ Projects Overview

This repository contains isolated, highly modular projects. Each project is self-contained with its own implementation, headers, and build configuration.

### 1. [Thread-Safe LRU Cache](./projects/lru-cache)

A highly efficient, concurrent Least Recently Used (LRU) cache template class.

- **Core Concepts:** Hash maps, Doubly Linked Lists, Fine-grained Locking (`std::mutex`), Template Meta-programming.
- **Use Case:** Fast, key-value lookups with automated item eviction in highly multi-threaded application environments.

### 2. [Concurrent Connection Pool](./projects/connection-pool)

A robust resource manager designed to multiplex and reuse expensive network/database connections among worker threads.

- **Core Concepts:** Resource allocation tracking, Resource Acquisition Is Initialization (RAII), Move semantics (`std::unique_ptr`), FIFO synchronization.
- **Use Case:** Preventing thread-creation overhead and socket exhaustion in heavy backend network architectures.

---

## 🚀 Getting Started

### Prerequisites

- A modern C++ compiler supporting **C++17** or higher (GCC, Clang, or MSVC)
- CMake (version 3.10+)

### Building the Workspace

To build all projects simultaneously from the root directory:

```bash
mkdir build && cd build
cmake ..
make
```
