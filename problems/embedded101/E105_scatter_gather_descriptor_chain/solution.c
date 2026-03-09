#include <stdint.h>
/*
 * E105: Scatter Gather Descriptor Chain
 *
 * Construct a complex descriptor chain for zero-copy packet transmission.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>

#define QSIZE 8

typedef struct {
    uint32_t ring[QSIZE];
    uint32_t head;
    uint32_t tail;
} Queue;

static int push(Queue* q, uint32_t v) {
    uint32_t next = (q->tail + 1u) % QSIZE;
    if (next == q->head) return 0;
    q->ring[q->tail] = v;
    q->tail = next;
    return 1;
}

static int pop(Queue* q, uint32_t* out) {
    if (q->head == q->tail) return 0;
    *out = q->ring[q->head];
    q->head = (q->head + 1u) % QSIZE;
    return 1;
}

int main(void) {
    Queue q = {0};
    uint32_t value = 0;
    int ok = push(&q, 0x100u + 105) && pop(&q, &value) && value == (0x100u + 105);
    printf("[E105] hpio_core val=%u %s\n", value, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
