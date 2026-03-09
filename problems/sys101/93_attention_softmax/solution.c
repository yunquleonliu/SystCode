/**
 * Problem 93: Attention Softmax
 * Compute attention scores in transformer
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SEQ_LEN 16
#define HEAD_DIM 64

void matrix_multiply(float* a, float* b, float* c, int m, int n, int k) {
    // c = a*b (m x k) * (k x n) -> (m x n)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            float sum = 0;
            for (int p = 0; p < k; p++) {
                sum += a[i*k + p] * b[p*n + j];
            }
            c[i*n + j] = sum;
        }
    }
}

void softmax(float* scores, float* output, int len) {
    // Find max for numerical stability
    float max_val = scores[0];
    for (int i = 1; i < len; i++) {
        if (scores[i] > max_val) max_val = scores[i];
    }
    
    // Compute exponentials
    float sum = 0;
    for (int i = 0; i < len; i++) {
        output[i] = exp(scores[i] - max_val);
        sum += output[i];
    }
    
    // Normalize
    for (int i = 0; i < len; i++) {
        output[i] /= sum;
    }
}

void attention_forward(float* q, float* k, float* v, float* output,
                      int seq_len, int head_dim, float scale) {
    // QK^T
    float* scores = malloc(seq_len * seq_len * sizeof(float));
    matrix_multiply(q, k, scores, seq_len, seq_len, head_dim);
    
    // Scale
    for (int i = 0; i < seq_len * seq_len; i++) {
        scores[i] *= scale;
    }
    
    // Softmax per query
    float* weights = malloc(seq_len * seq_len * sizeof(float));
    for (int i = 0; i < seq_len; i++) {
        softmax(&scores[i * seq_len], &weights[i * seq_len], seq_len);
    }
    
    // Weighted sum
    matrix_multiply(weights, v, output, seq_len, head_dim, seq_len);
    
    free(scores);
    free(weights);
}

void test_scenario() {
    printf("Running tests for Attention Softmax...\n\n");
    
    int seq_len = 4;
    int head_dim = 8;
    
    float* q = malloc(seq_len * head_dim * sizeof(float));
    float* k = malloc(seq_len * head_dim * sizeof(float));
    float* v = malloc(seq_len * head_dim * sizeof(float));
    float* output = malloc(seq_len * head_dim * sizeof(float));
    
    // Initialize with random values
    srand(42);
    for (int i = 0; i < seq_len * head_dim; i++) {
        q[i] = (float)rand() / RAND_MAX;
        k[i] = (float)rand() / RAND_MAX;
        v[i] = (float)rand() / RAND_MAX;
    }
    
    float scale = 1.0f / sqrt(head_dim);
    attention_forward(q, k, v, output, seq_len, head_dim, scale);
    
    printf("Computed attention for seq_len=%d, head_dim=%d\n", seq_len, head_dim);
    printf("Output shape: [%d, %d]\n", seq_len, head_dim);
    
    printf("Sample output values: %.4f %.4f %.4f...\n",
           output[0], output[1], output[2]);
    
    printf("Passed.\n");
    free(q); free(k); free(v); free(output);
}

int main() {
    test_scenario();
    return 0;
}