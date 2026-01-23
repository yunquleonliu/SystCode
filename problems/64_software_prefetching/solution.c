/**
 * Problem 64: Software Prefetching - Cache Warmup
 * Optimize memory access with explicit prefetch hints
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1000000

int array_sum_no_prefetch(int* data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

int array_sum_prefetch(int* data, int size) {
    int sum = 0;
    int prefetch_distance = 8;
    
    for (int i = 0; i < size; i++) {
        if (i + prefetch_distance < size) {
            __builtin_prefetch(&data[i + prefetch_distance], 0, 3);
        }
        sum += data[i];
    }
    return sum;
}

void test_scenario() {
    printf("Running tests for Software Prefetching...\n\n");
    
    int* data = malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        data[i] = i % 1000;
    }
    
    struct timespec start, end;
    int result;
    
    // Without prefetch
    clock_gettime(CLOCK_MONOTONIC, &start);
    result = array_sum_no_prefetch(data, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double no_prefetch = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    
    // With prefetch
    clock_gettime(CLOCK_MONOTONIC, &start);
    result = array_sum_prefetch(data, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double with_prefetch = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    
    printf("No prefetch: %.2f ms\n", no_prefetch / 1e6);
    printf("With prefetch: %.2f ms\n", with_prefetch / 1e6);
    printf("Improvement: %.2f%%\n", (1 - with_prefetch / no_prefetch) * 100);
    printf("Passed.\n");
    
    free(data);
}

int main() {
    test_scenario();
    return 0;
}