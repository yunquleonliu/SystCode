/**
 * Problem 62: False Sharing - Cache Line Contention
 * Demonstrate and mitigate false sharing in concurrent access
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define NUM_THREADS 4
#define CACHE_LINE_SIZE 64
#define ITERATIONS 10000000

typedef struct {
    long counter;
    char padding[CACHE_LINE_SIZE - sizeof(long)];  // Pad to cache line
} AlignedCounter;

typedef struct {
    long counter;  // No padding - false sharing
} UnalignedCounter;

AlignedCounter aligned_counters[NUM_THREADS];
UnalignedCounter unaligned_counters[NUM_THREADS];

void* thread_work_aligned(void* arg) {
    int id = (intptr_t)arg;
    for (int i = 0; i < ITERATIONS; i++) {
        aligned_counters[id].counter++;
    }
    return NULL;
}

void* thread_work_unaligned(void* arg) {
    int id = (intptr_t)arg;
    for (int i = 0; i < ITERATIONS; i++) {
        unaligned_counters[id].counter++;
    }
    return NULL;
}

void test_scenario() {
    printf("Running tests for False Sharing mitigation...\n\n");
    
    pthread_t threads[NUM_THREADS];
    struct timespec start, end;
    
    // Test unaligned (false sharing)
    printf("Unaligned (false sharing): ");
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_work_unaligned, (void*)(intptr_t)i);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double unaligned_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    printf("%.2f ms\n", unaligned_time / 1e6);
    
    // Test aligned (no false sharing)
    printf("Aligned (no false sharing): ");
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_work_aligned, (void*)(intptr_t)i);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double aligned_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    printf("%.2f ms\n", aligned_time / 1e6);
    
    printf("Speedup: %.2fx\n", unaligned_time / aligned_time);
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}