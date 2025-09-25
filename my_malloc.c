#include "malloc.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

typedef struct block
{
    size_t size;
    int is_free;
    struct block *next;
} block_t;

static block_t *heap_start = NULL;

#define MIN_BLOCK_SIZE 32
#define BLOCK_HEADER_SIZE sizeof(block_t)

static size_t align_size(size_t size)
{
    return (size + 7) & ~7;
}

static block_t *find_free_block(size_t size)
{
    block_t *current = heap_start;

    while (current)
    {
        if (current->is_free && current->size >= size)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static void split_block(block_t *block, size_t size)
{
    if (block->size < size + BLOCK_HEADER_SIZE + MIN_BLOCK_SIZE)
    {
       
        return;
    }

    block_t *new_block = (block_t *)((char *)block + BLOCK_HEADER_SIZE + size);
    new_block->size = block->size - size - BLOCK_HEADER_SIZE;
    new_block->is_free = 1;
    new_block->next = block->next;

    block->size = size;
    block->next = new_block;
}

#define HEAP_SIZE (1024 * 1024 * 10)
static char heap_buffer[HEAP_SIZE];
static size_t heap_offset = 0;
static int heap_initialized = 0;

static block_t *request_space(size_t size)
{
    size_t total_size = BLOCK_HEADER_SIZE + size;

    if (heap_offset + total_size > HEAP_SIZE)
    {
        return NULL; 
    }

    block_t *block = (block_t *)(heap_buffer + heap_offset);
    heap_offset += total_size;

    block->size = size;
    block->is_free = 0;
    block->next = NULL;

    return block;
}


void *my_malloc(size_t size)
{
    if (size <= 0)
    {
        return NULL;
    }

   
    if (!heap_initialized)
    {
        heap_initialized = 1;
        printf("Initialized heap with %d MB buffer\n", HEAP_SIZE / (1024 * 1024));
    }

    size = align_size(size);

    block_t *block;

    if (!heap_start)
    {

        block = request_space(size);
        if (!block)
        {
            return NULL;
        }
        heap_start = block;
    }
    else
    {

        block = find_free_block(size);

        if (block)
        {

            block->is_free = 0;
            split_block(block, size);
        }
        else
        {
           
            block = request_space(size);
            if (!block)
            {
                return NULL;
            }

            block_t *current = heap_start;
            while (current->next)
            {
                current = current->next;
            }
            current->next = block;
        }
    }

    return (char *)block + BLOCK_HEADER_SIZE;
}

void print_heap_info(void)
{
    printf("\n=== HEAP INFO ===\n");

    if (!heap_start)
    {
        printf("Heap is empty\n");
        printf("==================\n\n");
        return;
    }

    block_t *current = heap_start;
    int block_count = 0;
    int allocated_count = 0;
    size_t total_size = 0;
    size_t allocated_size = 0;

    while (current)
    {
        printf("Block %d: size=%zu, %s, addr=%p\n",
               block_count, current->size,
               current->is_free ? "FREE" : "ALLOCATED",
               (void *)current);

        total_size += current->size + BLOCK_HEADER_SIZE;

        if (!current->is_free)
        {
            allocated_count++;
            allocated_size += current->size;
        }

        current = current->next;
        block_count++;
    }

    printf("Total blocks: %d\n", block_count);
    printf("Allocated blocks: %d\n", allocated_count);
    printf("Total heap size: %zu bytes\n", total_size);
    printf("Allocated data size: %zu bytes\n", allocated_size);
    printf("Header overhead: %zu bytes\n", block_count * BLOCK_HEADER_SIZE);
    printf("Heap buffer used: %zu / %d bytes (%.1f%%)\n",
           heap_offset, HEAP_SIZE, (heap_offset * 100.0) / HEAP_SIZE);
    printf("==================\n\n");
}

int get_allocated_blocks(void)
{
    int count = 0;
    block_t *current = heap_start;

    while (current)
    {
        if (!current->is_free)
        {
            count++;
        }
        current = current->next;
    }

    return count;
}


size_t get_total_heap_size(void)
{
    size_t total = 0;
    block_t *current = heap_start;

    while (current)
    {
        total += current->size + BLOCK_HEADER_SIZE;
        current = current->next;
    }

    return total;
}