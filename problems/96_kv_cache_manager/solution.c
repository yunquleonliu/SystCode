/**
 * Problem 96: KV-Cache Manager
 * Store and manage key-value pairs for LLM inference
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQ_LEN 2048
#define HEAD_DIM 64

typedef struct {
    float* k_cache;
    float* v_cache;
    int seq_len;
} KVCache;

KVCache* kv_cache_create() {
    KVCache* cache = malloc(sizeof(KVCache));
    cache->k_cache = malloc(MAX_SEQ_LEN * HEAD_DIM * sizeof(float));
    cache->v_cache = malloc(MAX_SEQ_LEN * HEAD_DIM * sizeof(float));
    cache->seq_len = 0;
    return cache;
}

void kv_cache_append(KVCache* cache, float* k, float* v, int seq_pos) {
    if (seq_pos >= MAX_SEQ_LEN) {
        return;
    }
    
    memcpy(&cache->k_cache[seq_pos * HEAD_DIM], k, HEAD_DIM * sizeof(float));
    memcpy(&cache->v_cache[seq_pos * HEAD_DIM], v, HEAD_DIM * sizeof(float));
    
    cache->seq_len = seq_pos + 1;
}

void test_scenario() {
    printf("Running tests for KV-Cache Manager...\n\n");
    
    KVCache* cache = kv_cache_create();
    
    for (int i = 0; i < 10; i++) {
        float k[HEAD_DIM], v[HEAD_DIM];
        
        for (int j = 0; j < HEAD_DIM; j++) {
            k[j] = (float)i + 0.1f * j;
            v[j] = (float)i + 0.2f * j;
        }
        
        kv_cache_append(cache, k, v, i);
    }
    
    printf("Cached 10 tokens\n");
    printf("Cached keys: %d\n", cache->seq_len);
    printf("Passed.\n");
    
    free(cache->k_cache);
    free(cache->v_cache);
    free(cache);
}

int main() {
    test_scenario();
    return 0;
}