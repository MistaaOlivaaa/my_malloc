# Custom Malloc Implementation

A simplified but functional implementation of malloc in C, built from scratch to demonstrate dynamic memory allocation concepts.

## 📋 Overview

This project implements a custom memory allocator similar to the standard library's `malloc()` function. It manages memory blocks using a linked list structure and provides debugging utilities to visualize heap status.

## 🌟 Features

- **Dynamic Memory Allocation**: Custom `my_malloc()` function
- **Block Management**: Linked list of memory blocks with headers
- **Memory Alignment**: 8-byte alignment for optimal performance
- **Block Splitting**: Splits large blocks to minimize waste
- **Cross-Platform**: Works on Windows (MinGW), Linux, and macOS
- **Debug Utilities**: Heap visualization and statistics
- **No System Dependencies**: Uses static buffer instead of system calls

## 🏗️ Architecture

### Memory Layout
```
[Header 24 bytes][User Data][Header 24 bytes][User Data]...
```

### Block Header Structure
```c
typedef struct block {
    size_t size;           // Size of data portion
    int is_free;          // 1 if free, 0 if allocated
    struct block* next;   // Pointer to next block
} block_t;
```

### Key Components

- **Static Heap Buffer**: 10MB pre-allocated buffer
- **Free List**: Linked list of all blocks (free and allocated)
- **First-Fit Algorithm**: Finds first available block that fits
- **Block Splitting**: Divides large blocks when possible

## 📁 Project Structure

```
my_malloc/
├── my_malloc.h          # Header file with function declarations
├── my_malloc.c          # Implementation of malloc and utilities
├── main.c              # Comprehensive test suite
└── README.md           # This file
```

## 🚀 Quick Start

### Prerequisites
- GCC compiler or compatible C compiler
- Works on Windows (MinGW), Linux, macOS

### Installation & Compilation
```bash
# Clone the repository
git clone https://github.com/MistaaOlivaaa/my_malloc.git
cd my_malloc


gcc -o malloc_test my_malloc.c main.c


./malloc_test
```

### Basic Usage
```c
#include "my_malloc.h"

int main() {
    
    void* ptr = my_malloc(100);
    
    if (ptr) {
        
        strcpy((char*)ptr, "Hello, World!");
        printf("Data: %s\n", (char*)ptr);
        
        
        print_heap_info();
    }
    
    return 0;
}
```

## 🧪 Test Suite

The included test program demonstrates:

1. **Basic Allocation** - Multiple different-sized blocks
2. **Data Storage** - String and array manipulation  
3. **Structure Allocation** - Custom data types
4. **Large Allocation** - 1MB block allocation
5. **Multiple Small Blocks** - Fragmentation testing
6. **Edge Cases** - Zero-size and 1-byte allocations

### Sample Output
```
=== TEST 1: Basic Allocation ===
Allocated three blocks:
  ptr1 (100 bytes): 0x404040
  ptr2 (200 bytes): 0x4040a8
  ptr3 (50 bytes):  0x404178

=== HEAP INFO ===
Block 0: size=104, ALLOCATED, addr=0x404040
Block 1: size=200, ALLOCATED, addr=0x4040a8
Block 2: size=56, ALLOCATED, addr=0x404178
Total blocks: 3
Allocated blocks: 3
Total heap size: 432 bytes
==================
```

## 🔧 API Reference

### Functions

#### `void* my_malloc(size_t size)`
Allocates memory block of specified size.
- **Parameters**: `size` - Number of bytes to allocate
- **Returns**: Pointer to allocated memory, or NULL if allocation fails
- **Notes**: Memory is not initialized

#### `void print_heap_info(void)`
Prints detailed information about current heap status including:
- All blocks with sizes and status
- Memory addresses  
- Total heap statistics
- Buffer usage percentage

#### `int get_allocated_blocks(void)`
Returns the number of currently allocated blocks.

#### `size_t get_total_heap_size(void)`  
Returns total heap size in bytes including headers.

## 🎯 How It Works

### Allocation Process
1. **Size Validation**: Checks if requested size is valid
2. **Alignment**: Aligns size to 8-byte boundaries
3. **Free Block Search**: Looks for existing free blocks
4. **Block Splitting**: Splits large blocks if beneficial
5. **New Block Creation**: Allocates from static buffer if needed

### Memory Management
- **Static Buffer**: 10MB buffer allocated at compile time
- **No System Calls**: Avoids platform-specific functions like `sbrk()`
- **Block Headers**: Each allocation has metadata header
- **Linked List**: All blocks connected for easy traversal

## 🔍 Implementation Details

### Alignment
All allocations are aligned to 8-byte boundaries for optimal CPU access:
```c
static size_t align_size(size_t size) {
    return (size + 7) & ~7;
}
```

### Block Splitting
Large free blocks are split to minimize waste:
```c
if (block->size >= size + HEADER_SIZE + MIN_BLOCK_SIZE) {
 
}
```

### Cross-Platform Compatibility
Uses static buffer instead of system calls:
```c
#define HEAP_SIZE (1024 * 1024 * 10)  
static char heap_buffer[HEAP_SIZE];
```

## 🚧 Limitations

- **No Free Function**: Memory cannot be freed (malloc-only implementation)
- **Fixed Heap Size**: Limited to 10MB total allocation
- **No Coalescing**: Adjacent free blocks aren't merged (since no free())
- **Simplified Design**: Missing advanced features like multiple size classes

## 🎓 Learning Objectives

This project demonstrates:
- **Dynamic Memory Management**: How allocators work internally
- **Data Structures**: Linked lists for block management
- **Memory Layout**: Headers, alignment, fragmentation
- **System Programming**: Low-level memory operations
- **Cross-Platform Development**: Portable C code

## 🛠️ Extending the Project

Possible enhancements:
- Add `my_free()` function with coalescing
- Implement `my_realloc()` for resizing blocks
- Add multiple size classes for better performance
- Implement best-fit or worst-fit allocation strategies
- Add memory debugging and leak detection
- Thread safety with mutex locks

## 📊 Performance Characteristics

- **Time Complexity**: O(n) for allocation (linear search)
- **Space Complexity**: O(1) additional space per block (header)
- **Memory Overhead**: 24 bytes per allocation (on 64-bit systems)
- **Fragmentation**: Minimized through block splitting

## 🤝 Contributing

Feel free to fork this project and submit improvements:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality  
5. Submit a pull request


## 🔗 References

- [The C Programming Language](https://en.wikipedia.org/wiki/The_C_Programming_Language)
- [Dynamic Memory Allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation)
- [Memory Management](https://en.wikipedia.org/wiki/Memory_management)



