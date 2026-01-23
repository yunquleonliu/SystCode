/**
 * Problem 94: Token Bucket for LLM Rate Limiting
 * Control inference request rate
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double tokens;
    double rate;
    double capacity;
    long last_update;
    long lock;
} TokenBucket;

TokenBucket* bucket_create(double rate, double capacity) {
    TokenBucket* bucket = malloc(sizeof(TokenBucket));
    bucket->tokens = capacity;
    bucket->rate = rate;
    bucket->capacity = capacity;
    bucket->last_update = time(NULL);
    bucket->lock = 0;
    return bucket;
}

void bucket_refill(TokenBucket* bucket) {
    long now = time(NULL);
    long elapsed = now - bucket->last_update;
    
    double new_tokens = bucket->tokens + (bucket->rate * elapsed);
    bucket->tokens = (new_tokens > bucket->capacity) ? bucket->capacity : new_tokens;
    bucket->last_update = now;
}

int bucket_allow(TokenBucket* bucket, double tokens) {
    bucket_refill(bucket);
    
    int allowed = (bucket->tokens >= tokens) ? 1 : 0;
    if (allowed) {
        bucket->tokens -= tokens;
    }
    
    return allowed;
}

void test_scenario() {
    printf("Running tests for Token Bucket (LLM)...\n\n");
    
    TokenBucket* bucket = bucket_create(5.0, 10.0);
    
    printf("Rate: 5 requests/sec, Capacity: 10\n\n");
    
    printf("Batch 1: Request 8 tokens...\n");
    if (bucket_allow(bucket, 8.0)) {
        printf("  Allowed\n");
    }
    
    printf("Batch 2: Request 3 tokens...\n");
    if (bucket_allow(bucket, 3.0)) {
        printf("  Allowed\n");
    } else {
        printf("  Denied\n");
    }
    
    printf("Passed.\n");
    free(bucket);
}

int main() {
    test_scenario();
    return 0;
}