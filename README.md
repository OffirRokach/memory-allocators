# Memory Allocators

This repository contains implementations of fixed-size and variable-size (dynamic) memory allocators.  
It was created for study purposes and to deepen understanding of memory management concepts in systems programming.

## Purpose

The primary goal of this project is to provide educational examples of how memory allocation can be managed at a low level.  
The code and concepts here are meant to help students and enthusiasts explore, experiment with, and learn about memory allocators and their inner workings.

## Allocators Implemented

- **Dynamic Allocator (Variable-Sized Allocator):**
  - Designed to handle memory blocks of varying sizes, allocating and freeing memory as needed.
  - Useful for understanding fragmentation, allocation strategies, and the challenges of dynamic memory management.

- **Fixed-Size Allocator:**
  - Allocates memory in fixed-size blocks from a pre-allocated pool.
  - Efficient and fast due to simple bookkeeping and constant-time operations.

## Usage

Feel free to browse the code, run and experiment with the allocators, and write further tests.  
Each allocator is implemented in a way that highlights key steps of memory allocation, deallocation, internal vs. external fragmentation, and management, along with the trade-offs of each approach.

## Disclaimer

This repository is for educational and study purposes only. The allocators provided may not be production-ready or suitable for use in critical systems. They are intentionally simple to make core concepts more accessible.
