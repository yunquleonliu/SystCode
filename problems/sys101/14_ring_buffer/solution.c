#include <stdio.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Lock-free Single-Producer Single-Consumer (SPSC) Ring Buffer
// Size must be power of 2
#define RING_SIZE 1024
#define MASK (RING_SIZE - 1)

typedef struct {
    int buffer[RING_SIZE];
    atomic_size_t head;
    atomic_size_t tail;
} RingBuffer;

void rb_init(RingBuffer* rb) {
    atomic_init(&rb->head, 0);
    atomic_init(&rb->tail, 0);
}

// Producer calls this
bool rb_push(RingBuffer* rb, int val) {
    size_t head = atomic_load_explicit(&rb->head, memory_order_relaxed);
    size_t tail = atomic_load_explicit(&rb->tail, memory_order_acquire); 
    
    // Check if full
    if ((head - tail) >= RING_SIZE) {
        return false;
    }

    rb->buffer[head & MASK] = val;
    // ensure data write happens before head update
    atomic_store_explicit(&rb->head, head + 1, memory_order_release); 
    return true;
}

// Consumer calls this
bool rb_pop(RingBuffer* rb, int* val) {
    size_t tail = atomic_load_explicit(&rb->tail, memory_order_relaxed);
    size_t head = atomic_load_explicit(&rb->head, memory_order_acquire); 
    
    if (tail == head) {
        return false; // Empty
    }

    *val = rb->buffer[tail & MASK];
    // ensure data read happens before tail update
    atomic_store_explicit(&rb->tail, tail + 1, memory_order_release); 
    return true;
}

void solution() {}

int main() {
    RingBuffer rb;
    rb_init(&rb);

    printf("Testing SPSC Ring Buffer...\n");

    if (rb_push(&rb, 42) && rb_push(&rb, 100)) {
        printf("Pushed 42, 100\n");
    }
    
    int val;
    if (rb_pop(&rb, &val)) {
        printf("Popped: %d\n", val);
        if (val == 42) printf("  Correct\n");
    }
    if (rb_pop(&rb, &val)) {
        printf("Popped: %d\n", val);
        if (val == 100) printf("  Correct\n");
    }

    if (!rb_pop(&rb, &val)) {
        printf("Buffer Empty (Correct)\n");
        printf("Test Passed\n");
    }

    return 0;
}
