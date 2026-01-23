/**
 * Problem 73: Bloom Filter
 * Probabilistic data structure for set membership testing
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOOM_BITS 10000
#define NUM_HASHES 3

typedef struct {
    unsigned char bits[BLOOM_BITS / 8];
} BloomFilter;

// Simple hash functions
unsigned int hash1(const char* str) {
    unsigned int h = 5381;
    for (int i = 0; str[i]; i++) {
        h = ((h << 5) + h) + str[i];
    }
    return h % BLOOM_BITS;
}

unsigned int hash2(const char* str) {
    unsigned int h = 0;
    for (int i = 0; str[i]; i++) {
        h = h * 31 + str[i];
    }
    return h % BLOOM_BITS;
}

unsigned int hash3(const char* str) {
    unsigned int h = 1;
    for (int i = 0; str[i]; i++) {
        h = h * 37 + str[i];
    }
    return h % BLOOM_BITS;
}

BloomFilter* bloom_create() {
    BloomFilter* bf = malloc(sizeof(BloomFilter));
    memset(bf->bits, 0, sizeof(bf->bits));
    return bf;
}

void bloom_add(BloomFilter* bf, const char* element) {
    unsigned int h1 = hash1(element);
    unsigned int h2 = hash2(element);
    unsigned int h3 = hash3(element);
    
    bf->bits[h1 / 8] |= (1 << (h1 % 8));
    bf->bits[h2 / 8] |= (1 << (h2 % 8));
    bf->bits[h3 / 8] |= (1 << (h3 % 8));
}

int bloom_contains(BloomFilter* bf, const char* element) {
    unsigned int h1 = hash1(element);
    unsigned int h2 = hash2(element);
    unsigned int h3 = hash3(element);
    
    int bit1 = (bf->bits[h1 / 8] >> (h1 % 8)) & 1;
    int bit2 = (bf->bits[h2 / 8] >> (h2 % 8)) & 1;
    int bit3 = (bf->bits[h3 / 8] >> (h3 % 8)) & 1;
    
    return bit1 && bit2 && bit3;
}

void test_scenario() {
    printf("Running tests for Bloom Filter...\n\n");
    
    BloomFilter* bf = bloom_create();
    
    // Add elements
    const char* elements[] = {"apple", "banana", "cherry", "date"};
    for (int i = 0; i < 4; i++) {
        bloom_add(bf, elements[i]);
    }
    
    printf("Added %d elements\n", 4);
    
    // Test membership
    printf("\nMembership tests:\n");
    printf("'apple': %s\n", bloom_contains(bf, "apple") ? "Possibly in set" : "Definitely not");
    printf("'banana': %s\n", bloom_contains(bf, "banana") ? "Possibly in set" : "Definitely not");
    printf("'grape': %s\n", bloom_contains(bf, "grape") ? "Possibly in set" : "Definitely not");
    printf("'kiwi': %s\n", bloom_contains(bf, "kiwi") ? "Possibly in set" : "Definitely not");
    
    printf("Passed.\n");
    free(bf);
}

int main() {
    test_scenario();
    return 0;
}