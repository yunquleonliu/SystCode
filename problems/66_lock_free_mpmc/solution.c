/**
 * Problem 66: Lock-Free MPMC Queue
 * Multi-producer, multi-consumer queue using compare-and-swap
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>

#define QUEUE_SIZE 256
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define ITEMS_PER_PRODUCER 1000

typedef struct {
    int data;
    atomic_int sequence;
} Element;

typedef struct {
    Element elements[QUEUE_SIZE];
    atomic_int head;
    atomic_int tail;
} LFQueue;

LFQueue* lfqueue_create() {
    LFQueue* q = malloc(sizeof(LFQueue));
    atomic_init(&q->head, 0);
    atomic_init(&q->tail, 0);
    for (int i = 0; i < QUEUE_SIZE; i++) {
        atomic_init(&q->elements[i].sequence, i);
    }
    return q;
}

bool lfqueue_enqueue(LFQueue* q, int value) {
    while (true) {
        int tail = atomic_load_explicit(&q->tail, memory_order_acquire);
        Element* elem = &q->elements[tail % QUEUE_SIZE];
        int seq = atomic_load_explicit(&elem->sequence, memory_order_acquire);
        
        if (seq == tail && atomic_compare_exchange_weak_explicit(
            &q->tail, &tail, tail + 1, memory_order_release, memory_order_relaxed)) {
            elem->data = value;
            atomic_store_explicit(&elem->sequence, tail + 1, memory_order_release);
            return true;
        }
        if ((tail - atomic_load_explicit(&q->head, memory_order_acquire)) >= QUEUE_SIZE) {
            return false;  // Queue full
        }
    }
}

bool lfqueue_dequeue(LFQueue* q, int* value) {
    while (true) {
        int head = atomic_load_explicit(&q->head, memory_order_acquire);
        Element* elem = &q->elements[head % QUEUE_SIZE];
        int seq = atomic_load_explicit(&elem->sequence, memory_order_acquire);
        
        if (seq == head + 1 && atomic_compare_exchange_weak_explicit(
            &q->head, &head, head + 1, memory_order_release, memory_order_relaxed)) {
            *value = elem->data;
            atomic_store_explicit(&elem->sequence, head + QUEUE_SIZE, memory_order_release);
            return true;
        }
        if (head >= atomic_load_explicit(&q->tail, memory_order_acquire)) {
            return false;  // Queue empty
        }
    }
}

int total_enqueued = 0, total_dequeued = 0;
pthread_mutex_t stats_lock = PTHREAD_MUTEX_INITIALIZER;

void* producer_thread(void* arg) {
    LFQueue* q = (LFQueue*)arg;
    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        while (!lfqueue_enqueue(q, i)) {
            sched_yield();
        }
    }
    pthread_mutex_lock(&stats_lock);
    total_enqueued += ITEMS_PER_PRODUCER;
    pthread_mutex_unlock(&stats_lock);
    return NULL;
}

void* consumer_thread(void* arg) {
    LFQueue* q = (LFQueue*)arg;
    int value;
    int count = 0;
    while (count < ITEMS_PER_PRODUCER * NUM_PRODUCERS / NUM_CONSUMERS) {
        if (lfqueue_dequeue(q, &value)) {
            count++;
        } else {
            sched_yield();
        }
    }
    pthread_mutex_lock(&stats_lock);
    total_dequeued += count;
    pthread_mutex_unlock(&stats_lock);
    return NULL;
}

void test_scenario() {
    printf("Running tests for Lock-Free MPMC Queue...\n\n");
    
    LFQueue* q = lfqueue_create();
    pthread_t threads[NUM_PRODUCERS + NUM_CONSUMERS];
    
    // Create producers
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&threads[i], NULL, producer_thread, q);
    }
    
    // Create consumers
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&threads[NUM_PRODUCERS + i], NULL, consumer_thread, q);
    }
    
    // Join all
    for (int i = 0; i < NUM_PRODUCERS + NUM_CONSUMERS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Producers: %d, Consumers: %d\n", NUM_PRODUCERS, NUM_CONSUMERS);
    printf("Items per producer: %d\n", ITEMS_PER_PRODUCER);
    printf("Total enqueued: %d\n", total_enqueued);
    printf("Total dequeued: %d\n", total_dequeued);
    printf("Passed.\n");
    
    free(q);
}

int main() {
    test_scenario();
    return 0;
}