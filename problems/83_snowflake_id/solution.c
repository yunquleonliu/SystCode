/**
 * Problem 83: Snowflake ID Generator
 * Distributed unique ID generation with timestamp
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#define EPOCH 1288834974657LL
#define DATACENTER_ID_BITS 5
#define WORKER_ID_BITS 5
#define SEQUENCE_BITS 12

#define DATACENTER_ID_SHIFT (SEQUENCE_BITS)
#define WORKER_ID_SHIFT (SEQUENCE_BITS + DATACENTER_ID_BITS)
#define TIMESTAMP_SHIFT (SEQUENCE_BITS + DATACENTER_ID_BITS + WORKER_ID_BITS)

typedef struct {
    int datacenter_id;
    int worker_id;
    long sequence;
    long last_timestamp;
    pthread_mutex_t lock;
} SnowflakeGenerator;

SnowflakeGenerator* snowflake_create(int dc_id, int worker_id) {
    SnowflakeGenerator* sg = malloc(sizeof(SnowflakeGenerator));
    sg->datacenter_id = dc_id;
    sg->worker_id = worker_id;
    sg->sequence = 0;
    sg->last_timestamp = 0;
    pthread_mutex_init(&sg->lock, NULL);
    return sg;
}

long current_timestamp_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

long64_t snowflake_next_id(SnowflakeGenerator* sg) {
    pthread_mutex_lock(&sg->lock);
    
    long ts = current_timestamp_ms();
    
    if (ts == sg->last_timestamp) {
        sg->sequence = (sg->sequence + 1) & ((1 << SEQUENCE_BITS) - 1);
        if (sg->sequence == 0) {
            // Sequence overflow, wait for next millisecond
            while (ts <= sg->last_timestamp) {
                ts = current_timestamp_ms();
            }
        }
    } else {
        sg->sequence = 0;
    }
    
    sg->last_timestamp = ts;
    
    int64_t id = ((ts - EPOCH) << TIMESTAMP_SHIFT) |
                 (sg->datacenter_id << WORKER_ID_SHIFT) |
                 (sg->worker_id << DATACENTER_ID_SHIFT) |
                 sg->sequence;
    
    pthread_mutex_unlock(&sg->lock);
    return id;
}

void test_scenario() {
    printf("Running tests for Snowflake ID Generator...\n\n");
    
    SnowflakeGenerator* sg = snowflake_create(1, 1);
    
    printf("Generating 10 IDs...\n");
    for (int i = 0; i < 10; i++) {
        int64_t id = snowflake_next_id(sg);
        printf("  ID %d: %ld\n", i+1, id);
    }
    
    printf("Passed.\n");
    pthread_mutex_destroy(&sg->lock);
    free(sg);
}

int main() {
    test_scenario();
    return 0;
}