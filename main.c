#include <stdio.h>
#include <string.h>
#include "malloc.h"

typedef struct
{
    int id;
    char name[32];
    double value;
} test_data_t;

void test_basic_allocation()
{
    printf("=== TEST 1: Basic Allocation ===\n");

    void *ptr1 = my_malloc(100);
    void *ptr2 = my_malloc(200);
    void *ptr3 = my_malloc(50);

    printf("Allocated three blocks:\n");
    printf("  ptr1 (100 bytes): %p\n", ptr1);
    printf("  ptr2 (200 bytes): %p\n", ptr2);
    printf("  ptr3 (50 bytes):  %p\n", ptr3);

    print_heap_info();
}

void test_data_storage()
{
    printf("=== TEST 2: Data Storage and Retrieval ===\n");

    char *str = (char *)my_malloc(50);
    if (str)
    {
        strcpy(str, "Hello, World!");
        printf("String stored: \"%s\"\n", str);
        printf("String address: %p\n", (void *)str);
    }

    int *numbers = (int *)my_malloc(5 * sizeof(int));
    if (numbers)
    {
        for (int i = 0; i < 5; i++)
        {
            numbers[i] = (i + 1) * 10;
        }

        printf("Integer array: ");
        for (int i = 0; i < 5; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
        printf("Array address: %p\n", (void *)numbers);
    }

    print_heap_info();
}

void test_struct_allocation()
{
    printf("=== TEST 3: Structure Allocation ===\n");

    test_data_t *data = (test_data_t *)my_malloc(sizeof(test_data_t));

    if (data)
    {
        data->id = 42;
        strcpy(data->name, "Test Structure");
        data->value = 3.14159;

        printf("Structure allocated and initialized:\n");
        printf("  ID: %d\n", data->id);
        printf("  Name: %s\n", data->name);
        printf("  Value: %.5f\n", data->value);
        printf("  Address: %p\n", (void *)data);
        printf("  Size: %zu bytes\n", sizeof(test_data_t));
    }

    print_heap_info();
}

void test_large_allocation()
{
    printf("=== TEST 4: Large Allocation ===\n");

    size_t large_size = 1024 * 1024;
    void *large_ptr = my_malloc(large_size);

    if (large_ptr)
    {
        printf("Successfully allocated %zu bytes (1MB)\n", large_size);
        printf("Large block address: %p\n", large_ptr);

        char *data = (char *)large_ptr;
        data[0] = 'A';
        data[large_size - 1] = 'Z';

        printf("First byte: %c, Last byte: %c\n", data[0], data[large_size - 1]);
    }
    else
    {
        printf("Failed to allocate large block\n");
    }

    print_heap_info();
}

void test_multiple_small_allocations()
{
    printf("=== TEST 5: Multiple Small Allocations ===\n");

    const int num_allocs = 10;
    void *ptrs[num_allocs];

    printf("Allocating %d small blocks (32 bytes each):\n", num_allocs);

    for (int i = 0; i < num_allocs; i++)
    {
        ptrs[i] = my_malloc(32);
        if (ptrs[i])
        {

            char *data = (char *)ptrs[i];
            sprintf(data, "Block_%02d", i);
            printf("  Block %d: %p -> \"%s\"\n", i, ptrs[i], data);
        }
    }

    print_heap_info();
}

void test_zero_and_invalid_allocations()
{
    printf("=== TEST 6: Edge Cases ===\n");

    void *zero_ptr = my_malloc(0);
    printf("malloc(0) returned: %p\n", zero_ptr);

    void *tiny_ptr = my_malloc(1);
    printf("malloc(1) returned: %p\n", tiny_ptr);

    if (tiny_ptr)
    {
        *((char *)tiny_ptr) = 'X';
        printf("Successfully wrote to 1-byte allocation: %c\n", *((char *)tiny_ptr));
    }

    print_heap_info();
}

void print_statistics()
{
    printf("=== FINAL STATISTICS ===\n");
    printf("Allocated blocks: %d\n", get_allocated_blocks());
    printf("Total heap size: %zu bytes\n", get_total_heap_size());
    printf("=========================\n\n");
}

int main()
{
    printf("Custom Malloc Implementation Test Suite\n");
    printf("=======================================\n\n");

    test_basic_allocation();
    test_data_storage();
    test_struct_allocation();
    test_large_allocation();
    test_multiple_small_allocations();
    test_zero_and_invalid_allocations();

    print_statistics();

    printf("All tests completed successfully!\n");
    printf("Note: Memory is not freed in this implementation,\n");
    printf("so all allocated blocks remain until program exit.\n");

    return 0;
}