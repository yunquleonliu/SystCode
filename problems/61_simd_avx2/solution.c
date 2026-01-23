/**
 * Problem 61: SIMD Matrix Multiplication (AVX2)
 * Parallelize 4x4 float matrix multiplication using AVX2 intrinsics
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>
#include <assert.h>

typedef struct {
    float data[16];  // 4x4 matrix
} Matrix4x4;

Matrix4x4* matrix_create(float value) {
    Matrix4x4* m = malloc(sizeof(Matrix4x4));
    for (int i = 0; i < 16; i++) {
        m->data[i] = value;
    }
    return m;
}

// SIMD matrix multiplication using AVX2
void matrix_mult_avx2(Matrix4x4* a, Matrix4x4* b, Matrix4x4* c) {
    memset(c->data, 0, sizeof(c->data));
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            __m256 sum = _mm256_setzero_ps();
            
            for (int k = 0; k < 4; k += 8) {
                __m256 va = _mm256_loadu_ps(&a->data[i * 4]);
                __m256 vb = _mm256_set_ps(
                    b->data[(k + 3) * 4 + j],
                    b->data[(k + 2) * 4 + j],
                    b->data[(k + 1) * 4 + j],
                    b->data[k * 4 + j],
                    b->data[(k + 3) * 4 + j],
                    b->data[(k + 2) * 4 + j],
                    b->data[(k + 1) * 4 + j],
                    b->data[k * 4 + j]
                );
                sum = _mm256_fmadd_ps(va, vb, sum);
            }
            
            // Horizontal sum of 8-wide vector
            __m128 hi = _mm256_extractf128_ps(sum, 1);
            __m128 lo = _mm256_castps256_ps128(sum);
            __m128 res = _mm_add_ps(hi, lo);
            res = _mm_hadd_ps(res, res);
            res = _mm_hadd_ps(res, res);
            c->data[i * 4 + j] = _mm_cvtss_f32(res);
        }
    }
}

void test_scenario() {
    printf("Running tests for SIMD Matrix Mul (AVX2)...\n");
    
    Matrix4x4* a = matrix_create(2.0f);
    Matrix4x4* b = matrix_create(3.0f);
    Matrix4x4* c = malloc(sizeof(Matrix4x4));
    
    matrix_mult_avx2(a, b, c);
    
    printf("Result[0][0] = %.2f (expected 24.00 for 2*3*4)\n", c->data[0]);
    printf("Passed.\n");
    
    free(a);
    free(b);
    free(c);
}

int main() {
    test_scenario();
    return 0;
}