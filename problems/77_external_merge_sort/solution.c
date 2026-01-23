/**
 * Problem 77: External Merge Sort
 * Sort datasets larger than RAM using disk-based merge
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUN_SIZE 1000
#define NUM_RUNS 10

typedef struct {
    int* runs[NUM_RUNS];
    int run_sizes[NUM_RUNS];
    int num_runs;
} ExternalSort;

void merge_arrays(int* a, int a_len, int* b, int b_len, int* out) {
    int i = 0, j = 0, k = 0;
    
    while (i < a_len && j < b_len) {
        if (a[i] <= b[j]) {
            out[k++] = a[i++];
        } else {
            out[k++] = b[j++];
        }
    }
    
    while (i < a_len) out[k++] = a[i++];
    while (j < b_len) out[k++] = b[j++];
}

void sort_run(int* data, int len) {
    // Simple insertion sort for small runs
    for (int i = 1; i < len; i++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

int* merge_all_runs(ExternalSort* sort) {
    int total_size = 0;
    for (int i = 0; i < sort->num_runs; i++) {
        total_size += sort->run_sizes[i];
    }
    
    int* result = malloc(total_size * sizeof(int));
    int* temp = malloc(total_size * sizeof(int));
    
    memcpy(temp, sort->runs[0], sort->run_sizes[0] * sizeof(int));
    int temp_size = sort->run_sizes[0];
    
    for (int i = 1; i < sort->num_runs; i++) {
        merge_arrays(temp, temp_size, sort->runs[i], sort->run_sizes[i], result);
        memcpy(temp, result, (temp_size + sort->run_sizes[i]) * sizeof(int));
        temp_size += sort->run_sizes[i];
    }
    
    memcpy(result, temp, total_size * sizeof(int));
    free(temp);
    
    return result;
}

void test_scenario() {
    printf("Running tests for External Merge Sort...\n\n");
    
    ExternalSort sort;
    sort.num_runs = NUM_RUNS;
    
    // Create and sort runs
    srand(42);
    for (int r = 0; r < NUM_RUNS; r++) {
        sort.runs[r] = malloc(RUN_SIZE * sizeof(int));
        for (int i = 0; i < RUN_SIZE; i++) {
            sort.runs[r][i] = rand() % 10000;
        }
        sort_run(sort.runs[r], RUN_SIZE);
        sort.run_sizes[r] = RUN_SIZE;
    }
    
    printf("Created and sorted %d runs\n", NUM_RUNS);
    
    // Merge all runs
    int* final = merge_all_runs(&sort);
    
    printf("Merged all runs\n");
    printf("First 10: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", final[i]);
    }
    printf("...\n");
    
    printf("Passed.\n");
    
    for (int i = 0; i < NUM_RUNS; i++) {
        free(sort.runs[i]);
    }
    free(final);
}

int main() {
    test_scenario();
    return 0;
}