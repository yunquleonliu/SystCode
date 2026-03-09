/**
 * Problem 03: Arena Allocator
 * A memory pool that allocates linearly and frees all at once.
 * O(1) allocation, perfect for parsing, frame allocators, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define ARENA_DEFAULT_SIZE (1024 * 1024)  // 1MB default
#define ARENA_ALIGNMENT 16

typedef struct ArenaBlock {
    struct ArenaBlock* next;
    size_t size;
    size_t used;
    char data[];  // Flexible array member
} ArenaBlock;

typedef struct Arena {
    ArenaBlock* current;
    ArenaBlock* first;
    size_t default_block_size;
} Arena;

static size_t align_up(size_t n, size_t align) {
    return (n + align - 1) & ~(align - 1);
}

static ArenaBlock* arena_block_create(size_t size) {
    ArenaBlock* block = (ArenaBlock*)malloc(sizeof(ArenaBlock) + size);
    if (!block) return NULL;
    block->next = NULL;
    block->size = size;
    block->used = 0;
    return block;
}

Arena* arena_create(size_t default_size) {
    Arena* arena = (Arena*)malloc(sizeof(Arena));
    if (!arena) return NULL;
    
    size_t block_size = default_size > 0 ? default_size : ARENA_DEFAULT_SIZE;
    ArenaBlock* block = arena_block_create(block_size);
    if (!block) {
        free(arena);
        return NULL;
    }
    
    arena->current = block;
    arena->first = block;
    arena->default_block_size = block_size;
    return arena;
}

void* arena_alloc(Arena* arena, size_t size) {
    if (!arena || size == 0) return NULL;
    
    size_t aligned_size = align_up(size, ARENA_ALIGNMENT);
    ArenaBlock* block = arena->current;
    
    // Check if current block has space
    if (block->used + aligned_size > block->size) {
        // Need new block
        size_t new_size = arena->default_block_size;
        if (aligned_size > new_size) new_size = aligned_size;
        
        ArenaBlock* new_block = arena_block_create(new_size);
        if (!new_block) return NULL;
        
        block->next = new_block;
        arena->current = new_block;
        block = new_block;
    }
    
    void* ptr = block->data + block->used;
    block->used += aligned_size;
    return ptr;
}

void* arena_alloc_zero(Arena* arena, size_t size) {
    void* ptr = arena_alloc(arena, size);
    if (ptr) memset(ptr, 0, size);
    return ptr;
}

char* arena_strdup(Arena* arena, const char* str) {
    size_t len = strlen(str) + 1;
    char* copy = (char*)arena_alloc(arena, len);
    if (copy) memcpy(copy, str, len);
    return copy;
}

void arena_reset(Arena* arena) {
    if (!arena) return;
    // Reset all blocks to unused
    for (ArenaBlock* b = arena->first; b; b = b->next) {
        b->used = 0;
    }
    arena->current = arena->first;
}

void arena_destroy(Arena* arena) {
    if (!arena) return;
    ArenaBlock* block = arena->first;
    while (block) {
        ArenaBlock* next = block->next;
        free(block);
        block = next;
    }
    free(arena);
}

size_t arena_used(Arena* arena) {
    size_t total = 0;
    for (ArenaBlock* b = arena->first; b; b = b->next) {
        total += b->used;
    }
    return total;
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

void test_basic_allocation() {
    printf("Test: Basic allocation... ");
    Arena* arena = arena_create(4096);
    assert(arena != NULL);
    
    int* a = (int*)arena_alloc(arena, sizeof(int));
    int* b = (int*)arena_alloc(arena, sizeof(int));
    *a = 42;
    *b = 100;
    
    assert(*a == 42);
    assert(*b == 100);
    assert(a != b);
    
    arena_destroy(arena);
    printf("PASSED\n");
}

void test_alignment() {
    printf("Test: Alignment... ");
    Arena* arena = arena_create(4096);
    
    char* c = (char*)arena_alloc(arena, 1);
    double* d = (double*)arena_alloc(arena, sizeof(double));
    
    assert(((uintptr_t)d % ARENA_ALIGNMENT) == 0);
    
    arena_destroy(arena);
    printf("PASSED\n");
}

void test_block_growth() {
    printf("Test: Block growth... ");
    Arena* arena = arena_create(64);  // Small block
    
    // Allocate more than one block
    for (int i = 0; i < 100; i++) {
        int* p = (int*)arena_alloc(arena, sizeof(int));
        assert(p != NULL);
        *p = i;
    }
    
    arena_destroy(arena);
    printf("PASSED\n");
}

void test_reset() {
    printf("Test: Reset... ");
    Arena* arena = arena_create(4096);
    
    arena_alloc(arena, 1000);
    arena_alloc(arena, 1000);
    size_t used_before = arena_used(arena);
    
    arena_reset(arena);
    size_t used_after = arena_used(arena);
    
    assert(used_before > 0);
    assert(used_after == 0);
    
    arena_destroy(arena);
    printf("PASSED\n");
}

void test_strdup() {
    printf("Test: String duplication... ");
    Arena* arena = arena_create(4096);
    
    char* s1 = arena_strdup(arena, "Hello");
    char* s2 = arena_strdup(arena, "World");
    
    assert(strcmp(s1, "Hello") == 0);
    assert(strcmp(s2, "World") == 0);
    
    arena_destroy(arena);
    printf("PASSED\n");
}

int main() {
    printf("=== Arena Allocator Tests ===\n\n");
    test_basic_allocation();
    test_alignment();
    test_block_growth();
    test_reset();
    test_strdup();
    printf("\nAll tests passed!\n");
    return 0;
}
