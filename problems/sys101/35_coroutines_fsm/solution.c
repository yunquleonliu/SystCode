/**
 * Problem 35: Coroutines using FSM
 * Stackless coroutines with state machines.
 */

#include <stdio.h>
#include <stdlib.h>

// Duff's device style coroutine macros
#define CORO_BEGIN switch(coro->state) { case 0:
#define CORO_END } return -1;
#define CORO_YIELD(val) do { coro->state = __LINE__; return (val); case __LINE__:; } while(0)
#define CORO_RETURN(val) do { coro->state = -1; return (val); } while(0)

typedef struct {
    int state;
    // Local variables that need to persist
    int i;
    int n;
} Coroutine;

void coro_init(Coroutine* coro) {
    coro->state = 0;
    coro->i = 0;
    coro->n = 0;
}

// Generator: yields 0, 1, 2, ..., n-1
int range_generator(Coroutine* coro, int n) {
    CORO_BEGIN;
    
    coro->n = n;
    for (coro->i = 0; coro->i < coro->n; coro->i++) {
        CORO_YIELD(coro->i);
    }
    
    CORO_END;
}

// Fibonacci generator
typedef struct {
    int state;
    int a, b, temp;
    int count, max;
} FibCoro;

void fib_init(FibCoro* coro) {
    coro->state = 0;
}

int fib_generator(FibCoro* coro, int max) {
    switch(coro->state) {
    case 0:
        coro->a = 0;
        coro->b = 1;
        coro->max = max;
        coro->count = 0;
        
    case 1:
        while (coro->count < coro->max) {
            coro->state = 1;
            coro->temp = coro->a;
            coro->a = coro->b;
            coro->b = coro->temp + coro->b;
            coro->count++;
            return coro->temp;
        }
        coro->state = -1;
        return -1;
    }
    return -1;
}

// Producer-Consumer with coroutines
typedef struct {
    int state;
    int buffer[10];
    int count;
    int produced;
    int consumed;
} ProducerConsumer;

int producer(ProducerConsumer* pc) {
    switch(pc->state) {
    case 0:
        for (pc->produced = 0; pc->produced < 5; pc->produced++) {
            pc->buffer[pc->count++] = pc->produced * 10;
            printf("Produced: %d\n", pc->produced * 10);
            pc->state = 1;
            return 1;  // Yield to consumer
    case 1:;
        }
        pc->state = -1;
        return 0;
    }
    return 0;
}

int consumer(ProducerConsumer* pc) {
    switch(pc->state) {
    case 0:
    case 2:
        while (pc->count > 0) {
            int val = pc->buffer[--pc->count];
            printf("Consumed: %d\n", val);
            pc->consumed++;
            pc->state = 2;
            return 1;  // Yield
        }
        return 0;
    }
    return 0;
}

int main() {
    printf("=== Coroutines (FSM) ===\n\n");
    
    // Range generator
    printf("Range generator (0-4):\n");
    Coroutine range;
    coro_init(&range);
    int val;
    while ((val = range_generator(&range, 5)) >= 0) {
        printf("  %d\n", val);
    }
    
    // Fibonacci generator
    printf("\nFibonacci generator (10 numbers):\n");
    FibCoro fib;
    fib_init(&fib);
    printf(" ");
    while ((val = fib_generator(&fib, 10)) >= 0) {
        printf(" %d", val);
    }
    printf("\n");
    
    // Producer-Consumer
    printf("\nProducer-Consumer:\n");
    ProducerConsumer pc = {0};
    while (producer(&pc) || pc.count > 0) {
        consumer(&pc);
    }
    
    return 0;
}