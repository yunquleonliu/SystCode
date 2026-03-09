/**
 * Problem 34: Mini AddressSanitizer
 * Memory error detection (simplified).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define SHADOW_SCALE 3  // 1 shadow byte per 8 bytes
#define SHADOW_OFFSET 0x10000
#define REDZONE_SIZE 32

typedef struct {
    uint8_t* shadow_mem;
    size_t shadow_size;
    int errors;
} ASan;

typedef struct {
    void* ptr;
    size_t size;
    bool freed;
    char alloc_stack[256];
} Allocation;

#define MAX_ALLOCS 1000
Allocation allocs[MAX_ALLOCS];
int num_allocs = 0;
ASan asan;

void asan_init() {
    asan.shadow_size = 1024 * 1024;  // 1MB shadow
    asan.shadow_mem = calloc(1, asan.shadow_size);
    asan.errors = 0;
}

void asan_poison(void* addr, size_t size) {
    uintptr_t shadow_addr = ((uintptr_t)addr >> SHADOW_SCALE);
    if (shadow_addr < asan.shadow_size) {
        memset(asan.shadow_mem + shadow_addr, 0xFA, size >> SHADOW_SCALE);
    }
}

void asan_unpoison(void* addr, size_t size) {
    uintptr_t shadow_addr = ((uintptr_t)addr >> SHADOW_SCALE);
    if (shadow_addr < asan.shadow_size) {
        memset(asan.shadow_mem + shadow_addr, 0x00, size >> SHADOW_SCALE);
    }
}

bool asan_check(void* addr, size_t size) {
    uintptr_t shadow_addr = ((uintptr_t)addr >> SHADOW_SCALE);
    if (shadow_addr >= asan.shadow_size) return true;
    
    for (size_t i = 0; i < (size >> SHADOW_SCALE) + 1; i++) {
        if (asan.shadow_mem[shadow_addr + i] != 0) {
            return false;  // Poisoned
        }
    }
    return true;
}

void* asan_malloc(size_t size) {
    // Allocate with redzones
    size_t total = REDZONE_SIZE + size + REDZONE_SIZE;
    void* raw = malloc(total);
    if (!raw) return NULL;
    
    void* user_ptr = (char*)raw + REDZONE_SIZE;
    
    // Poison redzones
    asan_poison(raw, REDZONE_SIZE);
    asan_poison((char*)user_ptr + size, REDZONE_SIZE);
    
    // Unpoison user area
    asan_unpoison(user_ptr, size);
    
    // Track allocation
    Allocation* a = &allocs[num_allocs++];
    a->ptr = user_ptr;
    a->size = size;
    a->freed = false;
    snprintf(a->alloc_stack, 256, "asan_malloc(%zu)", size);
    
    printf("[ASan] malloc(%zu) -> %p\n", size, user_ptr);
    return user_ptr;
}

void asan_free(void* ptr) {
    if (!ptr) return;
    
    // Find allocation
    for (int i = 0; i < num_allocs; i++) {
        if (allocs[i].ptr == ptr) {
            if (allocs[i].freed) {
                printf("[ASan] ERROR: Double-free detected at %p\n", ptr);
                asan.errors++;
                return;
            }
            
            // Poison the memory
            asan_poison(ptr, allocs[i].size);
            allocs[i].freed = true;
            
            printf("[ASan] free(%p)\n", ptr);
            
            void* raw = (char*)ptr - REDZONE_SIZE;
            free(raw);
            return;
        }
    }
    
    printf("[ASan] ERROR: Invalid free (not allocated) at %p\n", ptr);
    asan.errors++;
}

void asan_check_access(void* addr, size_t size, const char* op) {
    if (!asan_check(addr, size)) {
        printf("[ASan] ERROR: %s of size %zu at %p is out of bounds!\n", 
               op, size, addr);
        asan.errors++;
    }
}

void asan_report() {
    printf("\n[ASan] Summary: %d error(s) detected\n", asan.errors);
}

int main() {
    printf("=== Mini AddressSanitizer ===\n\n");
    
    asan_init();
    
    // Normal allocation
    char* buf = asan_malloc(16);
    strcpy(buf, "Hello");
    asan_check_access(buf, 5, "write");
    
    // Buffer overflow (would be caught)
    printf("\nSimulating buffer overflow check...\n");
    asan_check_access(buf + 20, 4, "write");  // Out of bounds
    
    // Use after free
    asan_free(buf);
    printf("\nSimulating use-after-free check...\n");
    asan_check_access(buf, 4, "read");  // Use after free
    
    // Double free
    printf("\nSimulating double-free...\n");
    asan_free(buf);
    
    asan_report();
    
    free(asan.shadow_mem);
    return 0;
}