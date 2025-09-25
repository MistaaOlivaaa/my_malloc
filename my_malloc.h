#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stddef.h>

/**
 * Custom malloc implementation
 * 
 * Allocates memory of the specified size and returns a pointer to it.
 * The memory is not initialized.
 * 
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or NULL if allocation fails
 */
void* my_malloc(size_t size);

/**
 * Debug function to print current heap information
 * 
 * Prints details about all blocks in the heap including:
 * - Block number, size, and status (free/allocated)
 * - Memory addresses
 * - Total heap statistics
 */
void print_heap_info(void);

/**
 * Get total number of allocated blocks
 * 
 * @return Number of currently allocated blocks
 */
int get_allocated_blocks(void);

/**
 * Get total heap size in bytes
 * 
 * @return Total size of heap including headers
 */
size_t get_total_heap_size(void);

#endif /* MY_MALLOC_H */