/**
 * Problem 04: Buddy System Allocator
 * Power-of-two memory allocation with coalescing.
 * Used in Linux kernel for page allocation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_ORDER 10  // Max block = 2^10 = 1024 units
#define MIN_BLOCK_SIZE 16
#define TOTAL_SIZE (MIN_BLOCK_SIZE * (1 << MAX_ORDER))

typedef struct Block {
    struct Block* next;
    int order;
    int is_free;
} Block;

typedef struct {
    Block* free_lists[MAX_ORDER + 1];  // One list per order
    char* memory;
    size_t total_size;
} BuddyAllocator;

static int get_order(size_t size) {
    size_t block_size = MIN_BLOCK_SIZE;
    int order = 0;
    while (block_size < size && order < MAX_ORDER) {
        block_size *= 2;
        order++;
    }
    return order;
}

static size_t order_to_size(int order) {
    return MIN_BLOCK_SIZE * (1 << order);
}

static Block* get_buddy(BuddyAllocator* ba, Block* block) {
    size_t offset = (char*)block - ba->memory;
    size_t block_size = order_to_size(block->order);
    size_t buddy_offset = offset ^ block_size;  // XOR to find buddy
    
    if (buddy_offset >= ba->total_size) return NULL;
    return (Block*)(ba->memory + buddy_offset);
}

static void list_remove(Block** list, Block* block) {
    Block** pp = list;
    while (*pp) {
        if (*pp == block) {
            *pp = block->next;
            return;
        }
        pp = &(*pp)->next;
    }
}

static void list_insert(Block** list, Block* block) {
    block->next = *list;
    *list = block;
}

BuddyAllocator* buddy_create() {
    BuddyAllocator* ba = (BuddyAllocator*)malloc(sizeof(BuddyAllocator));
    if (!ba) return NULL;
    
    ba->memory = (char*)malloc(TOTAL_SIZE);
    if (!ba->memory) {
        free(ba);
        return NULL;
    }
    
    ba->total_size = TOTAL_SIZE;
    memset(ba->free_lists, 0, sizeof(ba->free_lists));
    
    // Initialize with one big block
    Block* initial = (Block*)ba->memory;
    initial->order = MAX_ORDER;
    initial->is_free = 1;
    initial->next = NULL;
    ba->free_lists[MAX_ORDER] = initial;
    
    return ba;
}

void* buddy_alloc(BuddyAllocator* ba, size_t size) {
    if (!ba || size == 0) return NULL;
    
    // Account for header
    size_t total = size + sizeof(Block);
    int order = get_order(total);
    if (order > MAX_ORDER) return NULL;
    
    // Find smallest available block
    int current = order;
    while (current <= MAX_ORDER && !ba->free_lists[current]) {
        current++;
    }
    
    if (current > MAX_ORDER) return NULL;  // Out of memory
    
    // Split blocks until we get the right size
    while (current > order) {
        Block* block = ba->free_lists[current];
        ba->free_lists[current] = block->next;
        
        current--;
        size_t half_size = order_to_size(current);
        
        Block* buddy = (Block*)((char*)block + half_size);
        block->order = current;
        buddy->order = current;
        block->is_free = 1;
        buddy->is_free = 1;
        
        list_insert(&ba->free_lists[current], buddy);
        list_insert(&ba->free_lists[current], block);
    }
    
    // Allocate from free list
    Block* block = ba->free_lists[order];
    ba->free_lists[order] = block->next;
    block->is_free = 0;
    
    return (void*)(block + 1);  // Return pointer after header
}

void buddy_free(BuddyAllocator* ba, void* ptr) {
    if (!ba || !ptr) return;
    
    Block* block = (Block*)ptr - 1;
    block->is_free = 1;
    
    // Coalesce with buddy if possible
    while (block->order < MAX_ORDER) {
        Block* buddy = get_buddy(ba, block);
        if (!buddy || !buddy->is_free || buddy->order != block->order) {
            break;
        }
        
        // Remove buddy from free list
        list_remove(&ba->free_lists[block->order], buddy);
        
        // Merge: use lower address as new block
        if ((char*)buddy < (char*)block) {
            Block* tmp = block;
            block = buddy;
            buddy = tmp;
        }
        block->order++;
    }
    
    list_insert(&ba->free_lists[block->order], block);
}

void buddy_destroy(BuddyAllocator* ba) {
    if (!ba) return;
    free(ba->memory);
    free(ba);
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

void test_basic_alloc_free() {
    printf("Test: Basic alloc/free... ");
    BuddyAllocator* ba = buddy_create();
    assert(ba != NULL);
    
    void* p1 = buddy_alloc(ba, 32);
    assert(p1 != NULL);
    
    void* p2 = buddy_alloc(ba, 64);
    assert(p2 != NULL);
    assert(p1 != p2);
    
    buddy_free(ba, p1);
    buddy_free(ba, p2);
    
    buddy_destroy(ba);
    printf("PASSED\n");
}

void test_coalescing() {
    printf("Test: Buddy coalescing... ");
    BuddyAllocator* ba = buddy_create();
    
    void* p1 = buddy_alloc(ba, 256);
    void* p2 = buddy_alloc(ba, 256);
    
    buddy_free(ba, p1);
    buddy_free(ba, p2);
    
    // After freeing both, they should coalesce
    void* p3 = buddy_alloc(ba, 512);
    assert(p3 != NULL);
    
    buddy_destroy(ba);
    printf("PASSED\n");
}

void test_fragmentation() {
    printf("Test: Fragmentation handling... ");
    BuddyAllocator* ba = buddy_create();
    
    void* ptrs[16];
    for (int i = 0; i < 16; i++) {
        ptrs[i] = buddy_alloc(ba, 100);
        assert(ptrs[i] != NULL);
    }
    
    // Free every other one
    for (int i = 0; i < 16; i += 2) {
        buddy_free(ba, ptrs[i]);
    }
    
    // Free remaining
    for (int i = 1; i < 16; i += 2) {
        buddy_free(ba, ptrs[i]);
    }
    
    buddy_destroy(ba);
    printf("PASSED\n");
}

int main() {
    printf("=== Buddy System Allocator Tests ===\n\n");
    test_basic_alloc_free();
    test_coalescing();
    test_fragmentation();
    printf("\nAll tests passed!\n");
    return 0;
}
