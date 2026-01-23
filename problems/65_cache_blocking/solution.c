/**
 * Problem 65: Cache Blocking - Loop Tiling
 * Optimize matrix operations with cache-conscious blocking
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 512
#define BLOCK_SIZE 32

typedef float matrix_t[N][N];

void matmul_naive(matrix_t A, matrix_t B, matrix_t C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void matmul_blocked(matrix_t A, matrix_t B, matrix_t C) {
    memset(C, 0, sizeof(matrix_t));
    
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {
                // Process block
                int i_end = (ii + BLOCK_SIZE < N) ? ii + BLOCK_SIZE : N;
                int j_end = (jj + BLOCK_SIZE < N) ? jj + BLOCK_SIZE : N;
                int k_end = (kk + BLOCK_SIZE < N) ? kk + BLOCK_SIZE : N;
                
                for (int i = ii; i < i_end; i++) {
                    for (int j = jj; j < j_end; j++) {
                        float sum = C[i][j];
                        for (int k = kk; k < k_end; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }
            }
        }
    }
}

void test_scenario() {
    printf("Running tests for Cache Blocking...\n\n");
    
    matrix_t* A = malloc(sizeof(matrix_t));
    matrix_t* B = malloc(sizeof(matrix_t));
    matrix_t* C_naive = malloc(sizeof(matrix_t));
    matrix_t* C_blocked = malloc(sizeof(matrix_t));
    
    // Initialize
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            (*A)[i][j] = (i + j) * 0.001f;
            (*B)[i][j] = (i - j) * 0.001f;
        }
    }
    
    struct timespec start, end;
    
    printf("Matrix size: %dx%d\n", N, N);
    printf("Block size: %dx%d\n", BLOCK_SIZE, BLOCK_SIZE);
    
    // Naive
    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_naive(*A, *B, *C_naive);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double naive_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    // Blocked
    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_blocked(*A, *B, *C_blocked);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double blocked_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Naive: %.3f seconds\n", naive_time);
    printf("Blocked: %.3f seconds\n", blocked_time);
    printf("Speedup: %.2fx\n", naive_time / blocked_time);
    printf("Passed.\n");
    
    free(A); free(B); free(C_naive); free(C_blocked);
}

int main() {
    test_scenario();
    return 0;
}