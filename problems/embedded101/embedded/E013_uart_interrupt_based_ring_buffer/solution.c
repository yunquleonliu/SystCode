#include <stdio.h>

#define RING_SIZE 16

typedef struct {
    char data[RING_SIZE];
    int head;
    int tail;
} RingBuffer;

static int ring_push(RingBuffer* ring, char value) {
    int next = (ring->tail + 1) % RING_SIZE;
    if (next == ring->head) return 0;
    ring->data[ring->tail] = value;
    ring->tail = next;
    return 1;
}

static int ring_pop(RingBuffer* ring, char* out) {
    if (ring->head == ring->tail) return 0;
    *out = ring->data[ring->head];
    ring->head = (ring->head + 1) % RING_SIZE;
    return 1;
}

int main(void) {
    RingBuffer rx = {0};
    ring_push(&rx, 'A');
    ring_push(&rx, 'B');
    ring_push(&rx, 'C');

    char a = '\0', b = '\0', c = '\0';
    int ok = ring_pop(&rx, &a) && ring_pop(&rx, &b) && ring_pop(&rx, &c) &&
             a == 'A' && b == 'B' && c == 'C';
    printf("[E013] seq=%c%c%c %s\n", a, b, c, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
