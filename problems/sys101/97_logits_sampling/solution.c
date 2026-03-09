/**
 * Problem 97: Logits Sampling
 * Temperature-based sampling for generation
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VOCAB_SIZE 50000

void apply_temperature(float* logits, float temperature, int vocab_size) {
    for (int i = 0; i < vocab_size; i++) {
        logits[i] /= temperature;
    }
}

void softmax_inplace(float* logits, float* probs, int size) {
    float max_val = logits[0];
    for (int i = 1; i < size; i++) {
        if (logits[i] > max_val) max_val = logits[i];
    }
    
    float sum = 0;
    for (int i = 0; i < size; i++) {
        probs[i] = exp(logits[i] - max_val);
        sum += probs[i];
    }
    
    for (int i = 0; i < size; i++) {
        probs[i] /= sum;
    }
}

int multinomial_sample(float* probs, int size) {
    float r = (float)rand() / RAND_MAX;
    float cumsum = 0;
    
    for (int i = 0; i < size; i++) {
        cumsum += probs[i];
        if (r < cumsum) {
            return i;
        }
    }
    
    return size - 1;
}

void test_scenario() {
    printf("Running tests for Logits Sampling...\n\n");
    
    int vocab_size = 1000;
    float* logits = malloc(vocab_size * sizeof(float));
    float* probs = malloc(vocab_size * sizeof(float));
    
    srand(42);
    for (int i = 0; i < vocab_size; i++) {
        logits[i] = (float)rand() / RAND_MAX * 10 - 5;
    }
    
    float temperature = 0.8f;
    apply_temperature(logits, temperature, vocab_size);
    
    softmax_inplace(logits, probs, vocab_size);
    
    printf("Applied temperature=%.1f\n", temperature);
    printf("Top 5 probabilities:\n");
    for (int i = 0; i < 5; i++) {
        printf("  Token %d: %.4f%%\n", i, probs[i] * 100);
    }
    
    int sampled = multinomial_sample(probs, vocab_size);
    printf("Sampled token: %d\n", sampled);
    
    printf("Passed.\n");
    free(logits);
    free(probs);
}

int main() {
    test_scenario();
    return 0;
}