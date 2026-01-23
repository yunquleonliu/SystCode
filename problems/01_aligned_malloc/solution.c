#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/**
 * @brief Allocates size bytes of uninitialized storage whose alignment is specified by alignment.
 * 
 * @param size The number of bytes to allocate.
 * @param alignment The alignment value, which must be a power of two and a multiple of sizeof(void*).
 * @return void* A pointer to the allocated memory.
 */
void* aligned_malloc(size_t size, size_t alignment) {
    // Basic validation: alignment must be non-zero and a power of two.
    // Also, size must be > 0.
    if (size == 0 || alignment == 0 || (alignment & (alignment - 1)) != 0) {
        return NULL;
    }

    // We need to allocate enough space for:
    // 1. The requested 'size'.
    // 2. The 'alignment' overhead (worst case padding).
    // 3. Space to store the original pointer (sizeof(void*)) so we can free it later.
    //
    // The worst-case padding needed to align a pointer is (alignment - 1).
    // We also need sizeof(void*) bytes *before* the aligned pointer to store the original address.
    
    size_t total_size = size + alignment + sizeof(void*);
    
    void* raw_ptr = malloc(total_size);
    if (!raw_ptr) {
        return NULL;
    }

    // Determine the aligned address.
    // We start looking for an alignment boundary after reserving space for our metadata (sizeof(void*)).
    uintptr_t start_addr = (uintptr_t)raw_ptr + sizeof(void*);
    
    // Align up formula: (x + align - 1) & ~(align - 1)
    uintptr_t aligned_addr = (start_addr + (alignment - 1)) & ~(alignment - 1);
    
    void* ptr = (void*)aligned_addr;

    // Store the original 'raw_ptr' just before the aligned address.
    // We cast to void** effectively treating the memory immediately preceding 'ptr' as a void* storage slot.
    ((void**)ptr)[-1] = raw_ptr;

    return ptr;
}

/**
 * @brief Frees a block of memory previously allocated by aligned_malloc.
 * 
 * @param ptr Pointer to the memory block to free.
 */
void aligned_free(void* ptr) {
    if (!ptr) {
        return;
    }
    
    // Recover the original pointer stored immediately before the aligned address.
    void* raw_ptr = ((void**)ptr)[-1];
    
    free(raw_ptr);
}

// -----------------------------------------------------------------------------
// Test Suite
// -----------------------------------------------------------------------------

void test_basic_allocation() {
    printf("Test: Basic Allocation... ");
    void* p = aligned_malloc(100, 16);
    assert(p != NULL);
    assert(((uintptr_t)p % 16) == 0);
    aligned_free(p);
    printf("Passed.\n");
}

void test_alignment_correctness() {
    printf("Test: Alignment Correctness... ");
    size_t alignments[] = {8, 16, 32, 64, 128, 4096};
    for (int i = 0; i < 6; i++) {
        size_t align = alignments[i];
        void* p = aligned_malloc(123, align);
        assert(p != NULL);
        assert(((uintptr_t)p % align) == 0);
        
        // Verify we can write to the whole block
        memset(p, 0xFF, 123);
        
        aligned_free(p);
    }
    printf("Passed.\n");
}

void test_invalid_arguments() {
    printf("Test: Invalid Arguments... ");
    
    // Alignment not power of 2
    assert(aligned_malloc(100, 15) == NULL);
    assert(aligned_malloc(100, 33) == NULL);
    
    // Size 0
    assert(aligned_malloc(0, 16) == NULL);
    
    printf("Passed.\n");
}

void test_data_integrity() {
    printf("Test: Data Integrity... ");
    size_t size = 1024;
    size_t align = 32;
    int* p = (int*)aligned_malloc(size * sizeof(int), align);
    assert(p != NULL);
    
    for (int i = 0; i < size; i++) {
        p[i] = i;
    }
    
    for (int i = 0; i < size; i++) {
        assert(p[i] == i);
    }
    
    aligned_free(p);
    printf("Passed.\n");
}

int main() {
    printf("Running Aligned Malloc Tests:\n");
    test_basic_allocation();
    test_alignment_correctness();
    test_invalid_arguments();
    test_data_integrity();
    printf("All tests passed successfully.\n");
    return 0;
}
