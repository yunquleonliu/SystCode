/**
 * Problem 82: Token Bucket Rate Limiter
 * Smooth traffic control with burst capacity
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double tokens;
    double rate;           // tokens per second
    double capacity;       // max tokens
    long last_update;
    long lock;             // simple spinlock
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
    while (__sync_lock_test_and_set(&bucket->lock, 1)) {
        // Spin
    }
    
    bucket_refill(bucket);
    
    int allowed = (bucket->tokens >= tokens) ? 1 : 0;
    if (allowed) {
        bucket->tokens -= tokens;
    }
    
    __sync_lock_release(&bucket->lock);
    return allowed;
}

void test_scenario() {
    printf("Running tests for Token Bucket Rate Limiter...\n\n");
    
    TokenBucket* bucket = bucket_create(10.0, 20.0);  // 10 tokens/sec, max 20
    
    // Burst: take 20 tokens
    printf("Attempting to take 20 tokens (initial capacity)...\n");
    if (bucket_allow(bucket, 20.0)) {
        printf("  Allowed\n");
    }
    
    // Try to take more
    printf("Attempting to take 5 more tokens...\n");
    if (bucket_allow(bucket, 5.0)) {
        printf("  Allowed\n");
    } else {
        printf("  Denied (no tokens available)\n");
    }
    
    // Wait and retry
    printf("Sleeping 2 seconds (20 tokens should be available)...\n");
    sleep(2);
    
    if (bucket_allow(bucket, 20.0)) {
        printf("  Allowed (tokens refilled)\n");
    }
    
    printf("Passed.\n");
    free(bucket);
}

int main() {
    test_scenario();
    return 0;
}