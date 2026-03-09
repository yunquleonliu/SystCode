/**
 * Problem 68: Bitmap Scanning - Bit Manipulation
 * Find set bits and perform efficient bitmap operations
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int find_first_set_bit(unsigned long x) {
    if (x == 0) return -1;
    return __builtin_ctzl(x);  // Count trailing zeros
}

int find_last_set_bit(unsigned long x) {
    if (x == 0) return -1;
    return 63 - __builtin_clzl(x);  // Count leading zeros
}

int count_set_bits(unsigned long x) {
    return __builtin_popcountl(x);
}

unsigned long next_power_of_2(unsigned long x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}

void test_scenario() {
    printf("Running tests for Bitmap Scanning...\n\n");
    
    unsigned long bitmap = 0b1010100;
    printf("Bitmap: 0x%lx (binary: 1010100)\n\n", bitmap);
    
    int first = find_first_set_bit(bitmap);
    int last = find_last_set_bit(bitmap);
    int count = count_set_bits(bitmap);
    
    printf("First set bit at position: %d\n", first);
    printf("Last set bit at position: %d\n", last);
    printf("Number of set bits: %d\n", count);
    
    assert(first == 2);
    assert(last == 6);
    assert(count == 3);
    
    // Test power of 2
    unsigned long val = 1000;
    unsigned long pow2 = next_power_of_2(val);
    printf("\nNext power of 2 after %lu: %lu\n", val, pow2);
    assert(pow2 == 1024);
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}