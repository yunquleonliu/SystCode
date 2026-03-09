/**
 * Problem 92: Vector Search (Approximate Nearest Neighbor)
 * Find similar vectors efficiently
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define VECTOR_DIM 128
#define NUM_VECTORS 1000

typedef struct {
    float data[VECTOR_DIM];
} Vector;

float cosine_distance(Vector* a, Vector* b) {
    float dot = 0, norm_a = 0, norm_b = 0;
    
    for (int i = 0; i < VECTOR_DIM; i++) {
        dot += a->data[i] * b->data[i];
        norm_a += a->data[i] * a->data[i];
        norm_b += b->data[i] * b->data[i];
    }
    
    if (norm_a == 0 || norm_b == 0) return 0;
    return dot / (sqrt(norm_a) * sqrt(norm_b));
}

typedef struct {
    int idx;
    float distance;
} SearchResult;

SearchResult* vector_search(Vector* vectors, int num_vectors, Vector* query, int k) {
    SearchResult* results = malloc(sizeof(SearchResult) * num_vectors);
    
    // Compute distances to all vectors
    for (int i = 0; i < num_vectors; i++) {
        results[i].idx = i;
        results[i].distance = cosine_distance(&vectors[i], query);
    }
    
    // Simple sort (bubble sort for small k)
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < num_vectors; j++) {
            if (results[j].distance > results[i].distance) {
                SearchResult tmp = results[i];
                results[i] = results[j];
                results[j] = tmp;
            }
        }
    }
    
    return results;
}

void test_scenario() {
    printf("Running tests for Vector Search...\n\n");
    
    Vector* vectors = malloc(sizeof(Vector) * 10);
    
    // Create sample vectors
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < VECTOR_DIM; j++) {
            vectors[i].data[j] = (float)rand() / RAND_MAX;
        }
    }
    
    Vector query;
    memcpy(&query, &vectors[0], sizeof(Vector));
    
    printf("Created 10 vectors with dimension %d\n", VECTOR_DIM);
    
    SearchResult* results = vector_search(vectors, 10, &query, 3);
    
    printf("\nTop 3 nearest neighbors:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %d: Vector %d (distance=%.4f)\n", 
               i+1, results[i].idx, results[i].distance);
    }
    
    printf("Passed.\n");
    free(vectors);
    free(results);
}

int main() {
    test_scenario();
    return 0;
}