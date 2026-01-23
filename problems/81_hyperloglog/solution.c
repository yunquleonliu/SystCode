/**
 * Problem 81: HyperLogLog
 * Approximate unique count with minimal memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PRECISION 14
#define NUM_REGISTERS (1 << PRECISION)

typedef struct {
    unsigned char registers[NUM_REGISTERS];
    double alpha;
} HyperLogLog;

// Count leading zeros in binary representation
int count_leading_zeros(unsigned int val) {
    if (val == 0) return 32;
    int count = 0;
    for (int i = 31; i >= 0; i--) {
        if (val & (1 << i)) break;
        count++;
    }
    return count;
}

HyperLogLog* hll_create() {
    HyperLogLog* hll = malloc(sizeof(HyperLogLog));
    memset(hll->registers, 0, NUM_REGISTERS);
    
    if (PRECISION == 14) {
        hll->alpha = 0.7213 / (1.0 + 1.079 / NUM_REGISTERS);
    } else {
        hll->alpha = 0.5;
    }
    
    return hll;
}

void hll_add(HyperLogLog* hll, const char* element) {
    unsigned int hash = 0;
    for (int i = 0; element[i]; i++) {
        hash = hash * 31 + element[i];
    }
    
    int index = hash & (NUM_REGISTERS - 1);
    int lz = count_leading_zeros(hash >> PRECISION);
    
    if (lz + 1 > hll->registers[index]) {
        hll->registers[index] = lz + 1;
    }
}

unsigned long hll_count(HyperLogLog* hll) {
    double sum = 0;
    for (int i = 0; i < NUM_REGISTERS; i++) {
        sum += pow(2, -(double)hll->registers[i]);
    }
    
    double estimate = hll->alpha * NUM_REGISTERS * NUM_REGISTERS / sum;
    
    if (estimate <= 2.5 * NUM_REGISTERS) {
        int zeros = 0;
        for (int i = 0; i < NUM_REGISTERS; i++) {
            if (hll->registers[i] == 0) zeros++;
        }
        if (zeros > 0) {
            estimate = NUM_REGISTERS * log((double)NUM_REGISTERS / zeros);
        }
    }
    
    return (unsigned long)estimate;
}

void test_scenario() {
    printf("Running tests for HyperLogLog...\n\n");
    
    HyperLogLog* hll = hll_create();
    
    // Add 10000 unique elements
    for (int i = 0; i < 10000; i++) {
        char buf[32];
        snprintf(buf, 32, "element_%d", i);
        hll_add(hll, buf);
    }
    
    unsigned long count = hll_count(hll);
    printf("Added 10000 elements\n");
    printf("Estimated count: %lu\n", count);
    printf("Registers used: %d bytes\n", NUM_REGISTERS);
    
    double error = fabs(count - 10000.0) / 10000.0;
    printf("Error: %.2f%%\n", error * 100);
    printf("Passed.\n");
    
    free(hll);
}

int main() {
    test_scenario();
    return 0;
}