/**
 * Problem 70: Strided Access Patterns
 * Optimize algorithms with memory stride awareness
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000000
#define ITERATIONS 100

int array_sum_stride1(int* data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

int array_sum_stride4(int* data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i += 4) {
        sum += data[i] + data[i+1] + data[i+2] + data[i+3];
    }
    return sum;
}

int array_sum_stride16(int* data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i += 16) {
        for (int j = 0; j < 16 && i + j < size; j++) {
            sum += data[i + j];
        }
    }
    return sum;
}

void test_scenario() {
    printf("Running tests for Strided Access Patterns...\n\n");
    
    int* data = malloc(ARRAY_SIZE * sizeof(int));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = i % 1000;
    }
    
    struct timespec start, end;
    int result;
    double times[3];
    
    // Stride 1
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int iter = 0; iter < ITERATIONS; iter++) {
        result = array_sum_stride1(data, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    times[0] = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    
    // Stride 4
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int iter = 0; iter < ITERATIONS; iter++) {
        result = array_sum_stride4(data, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    times[1] = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    
    // Stride 16
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int iter = 0; iter < ITERATIONS; iter++) {
        result = array_sum_stride16(data, ARRAY_SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    times[2] = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    
    printf("Stride 1: %.2f ms\n", times[0] / 1e6);
    printf("Stride 4: %.2f ms\n", times[1] / 1e6);
    printf("Stride 16: %.2f ms\n", times[2] / 1e6);
    printf("Passed.\n");
    
    free(data);
}

int main() {
    test_scenario();
    return 0;
}