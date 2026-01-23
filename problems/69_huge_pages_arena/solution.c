/**
 * Problem 69: Huge Pages Arena Allocator
 * Allocate large memory regions using 2MB/1GB pages
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define HUGE_PAGE_2MB (2 * 1024 * 1024)
#define HUGE_PAGE_1GB (1024 * 1024 * 1024)
#define ARENA_SIZE (100 * 1024 * 1024)  // 100MB

typedef struct {
    void* memory;
    size_t size;
    size_t allocated;
    int uses_huge_pages;
} HugePageArena;

HugePageArena* arena_create_huge() {
    HugePageArena* arena = malloc(sizeof(HugePageArena));
    arena->size = ARENA_SIZE;
    
    #ifdef MAP_HUGETLB
    arena->memory = mmap(NULL, arena->size, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    arena->uses_huge_pages = (arena->memory != MAP_FAILED);
    #else
    arena->memory = malloc(arena->size);
    arena->uses_huge_pages = 0;
    #endif
    
    arena->allocated = 0;
    return arena;
}

void* arena_alloc(HugePageArena* arena, size_t size) {
    if (arena->allocated + size > arena->size) {
        return NULL;
    }
    
    void* ptr = (char*)arena->memory + arena->allocated;
    arena->allocated += size;
    return ptr;
}

void arena_reset(HugePageArena* arena) {
    arena->allocated = 0;
}

void arena_destroy(HugePageArena* arena) {
    #ifdef MAP_HUGETLB
    if (arena->uses_huge_pages) {
        munmap(arena->memory, arena->size);
    } else
    #endif
    {
        free(arena->memory);
    }
    free(arena);
}

void test_scenario() {
    printf("Running tests for Huge Pages Arena...\n\n");
    
    HugePageArena* arena = arena_create_huge();
    
    printf("Arena size: %lu MB\n", arena->size / (1024 * 1024));
    printf("Uses huge pages: %s\n", arena->uses_huge_pages ? "Yes" : "No");
    
    // Allocate some memory
    int* arr1 = (int*)arena_alloc(arena, 1000 * sizeof(int));
    float* arr2 = (float*)arena_alloc(arena, 5000 * sizeof(float));
    
    printf("Allocated: %zu bytes\n", arena->allocated);
    
    // Use the memory
    for (int i = 0; i < 1000; i++) {
        arr1[i] = i;
    }
    
    for (int i = 0; i < 5000; i++) {
        arr2[i] = i * 1.5f;
    }
    
    printf("Array access OK\n");
    printf("Passed.\n");
    
    arena_destroy(arena);
}

int main() {
    test_scenario();
    return 0;
}