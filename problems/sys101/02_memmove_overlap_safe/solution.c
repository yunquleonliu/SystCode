/**
 * Problem 02: memmove - Overlap Safe Memory Copy
 * 
 * Implement a memory copy function that correctly handles overlapping regions.
 * Unlike memcpy, memmove must work correctly when source and destination overlap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Copies n bytes from src to dest, handling overlapping memory regions.
 * 
 * Strategy:
 * - If dest < src: copy forward (low to high addresses)
 * - If dest > src: copy backward (high to low addresses)
 * - If dest == src: no-op
 */
void* my_memmove(void* dest, const void* src, size_t n) {
    if (dest == src || n == 0) {
        return dest;
    }
    
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    
    if (d < s) {
        // Copy forward: dest is before src
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        // Copy backward: dest is after src
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
    
    return dest;
}

/**
 * Optimized version using word-sized copies when possible
 */
void* my_memmove_optimized(void* dest, const void* src, size_t n) {
    if (dest == src || n == 0) return dest;
    
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    size_t word_size = sizeof(size_t);
    
    if (d < s) {
        // Forward copy with word alignment
        while (n > 0 && ((uintptr_t)d % word_size != 0)) {
            *d++ = *s++;
            n--;
        }
        size_t* dw = (size_t*)d;
        const size_t* sw = (const size_t*)s;
        while (n >= word_size) {
            *dw++ = *sw++;
            n -= word_size;
        }
        d = (unsigned char*)dw;
        s = (const unsigned char*)sw;
        while (n > 0) {
            *d++ = *s++;
            n--;
        }
    } else {
        // Backward copy
        d += n;
        s += n;
        while (n > 0 && ((uintptr_t)d % word_size != 0)) {
            *--d = *--s;
            n--;
        }
        size_t* dw = (size_t*)d;
        const size_t* sw = (const size_t*)s;
        while (n >= word_size) {
            *--dw = *--sw;
            n -= word_size;
        }
        d = (unsigned char*)dw;
        s = (const unsigned char*)sw;
        while (n > 0) {
            *--d = *--s;
            n--;
        }
    }
    return dest;
}

// -----------------------------------------------------------------------------
// Test Suite
// -----------------------------------------------------------------------------

void test_non_overlapping() {
    printf("Test: Non-overlapping copy... ");
    char src[] = "Hello, World!";
    char dest[32] = {0};
    my_memmove(dest, src, strlen(src) + 1);
    assert(strcmp(dest, "Hello, World!") == 0);
    printf("PASSED\n");
}

void test_overlap_dest_before_src() {
    printf("Test: Overlapping (dest < src)... ");
    char buffer[] = "0123456789";
    my_memmove(buffer + 1, buffer + 3, 5);
    assert(memcmp(buffer, "0345676789", 10) == 0);
    printf("PASSED\n");
}

void test_overlap_dest_after_src() {
    printf("Test: Overlapping (dest > src)... ");
    char buffer[] = "0123456789";
    my_memmove(buffer + 3, buffer, 5);
    assert(memcmp(buffer, "0120123489", 10) == 0);
    printf("PASSED\n");
}

void test_same_location() {
    printf("Test: Same source and dest... ");
    char buffer[] = "Hello";
    my_memmove(buffer, buffer, 5);
    assert(strcmp(buffer, "Hello") == 0);
    printf("PASSED\n");
}

void test_zero_length() {
    printf("Test: Zero length copy... ");
    char src[] = "Source";
    char dest[] = "Dest";
    my_memmove(dest, src, 0);
    assert(strcmp(dest, "Dest") == 0);
    printf("PASSED\n");
}

void test_large_buffer() {
    printf("Test: Large buffer with overlap... ");
    size_t size = 10000;
    char* buffer = malloc(size);
    for (size_t i = 0; i < size; i++) {
        buffer[i] = (char)(i % 256);
    }
    my_memmove(buffer + 2500, buffer, 5000);
    for (size_t i = 0; i < 5000; i++) {
        assert(buffer[2500 + i] == (char)(i % 256));
    }
    free(buffer);
    printf("PASSED\n");
}

int main() {
    printf("=== memmove Overlap-Safe Implementation Tests ===\n\n");
    test_non_overlapping();
    test_overlap_dest_before_src();
    test_overlap_dest_after_src();
    test_same_location();
    test_zero_length();
    test_large_buffer();
    printf("\nAll tests passed!\n");
    return 0;
}
