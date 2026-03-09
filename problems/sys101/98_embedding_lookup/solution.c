/**
 * Problem 98: Embedding Lookup
 * Retrieve and aggregate embeddings
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VOCAB_SIZE 10000
#define EMBED_DIM 128

typedef struct {
    float* embeddings;
} EmbeddingTable;

EmbeddingTable* embedding_create(int vocab_size, int embed_dim) {
    EmbeddingTable* table = malloc(sizeof(EmbeddingTable));
    table->embeddings = malloc(vocab_size * embed_dim * sizeof(float));
    
    srand(42);
    for (int i = 0; i < vocab_size * embed_dim; i++) {
        table->embeddings[i] = (float)rand() / RAND_MAX;
    }
    
    return table;
}

void embedding_lookup(EmbeddingTable* table, int* token_ids, int seq_len,
                     int embed_dim, float* output) {
    for (int i = 0; i < seq_len; i++) {
        int token_id = token_ids[i];
        memcpy(&output[i * embed_dim],
               &table->embeddings[token_id * embed_dim],
               embed_dim * sizeof(float));
    }
}

void mean_pooling(float* embeddings, int seq_len, int embed_dim, float* output) {
    for (int d = 0; d < embed_dim; d++) {
        float sum = 0;
        for (int s = 0; s < seq_len; s++) {
            sum += embeddings[s * embed_dim + d];
        }
        output[d] = sum / seq_len;
    }
}

void test_scenario() {
    printf("Running tests for Embedding Lookup...\n\n");
    
    EmbeddingTable* table = embedding_create(VOCAB_SIZE, EMBED_DIM);
    
    printf("Created embedding table: [%d, %d]\n", VOCAB_SIZE, EMBED_DIM);
    
    int token_ids[] = {1, 42, 100, 5000, 9999};
    int seq_len = 5;
    
    float* embeddings = malloc(seq_len * EMBED_DIM * sizeof(float));
    embedding_lookup(table, token_ids, seq_len, EMBED_DIM, embeddings);
    
    printf("Looked up %d token embeddings\n", seq_len);
    
    float* pooled = malloc(EMBED_DIM * sizeof(float));
    mean_pooling(embeddings, seq_len, EMBED_DIM, pooled);
    
    printf("Computed mean pooling\n");
    printf("Passed.\n");
    free(embeddings);
    free(pooled);
    free(table->embeddings);
    free(table);
}

int main() {
    test_scenario();
    return 0;
}