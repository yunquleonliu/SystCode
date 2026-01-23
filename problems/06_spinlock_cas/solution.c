/**
 * Problem 06: Spinlock with Compare-And-Swap
 * Low-level synchronization primitive using atomic operations.
 * Includes optimizations: exponential backoff, PAUSE instruction.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#define PAUSE() YieldProcessor()
#define THREAD_LOCAL __declspec(thread)
#else
#include <pthread.h>
#include <sched.h>
#define PAUSE() __builtin_ia32_pause()
#define THREAD_LOCAL __thread
#endif

// Simple Test-And-Set Spinlock
typedef struct {
    atomic_flag flag;
} TASLock;

void tas_init(TASLock* lock) {
    atomic_flag_clear(&lock->flag);
}

void tas_lock(TASLock* lock) {
    while (atomic_flag_test_and_set_explicit(&lock->flag, memory_order_acquire)) {
        // Spin - could add PAUSE() here for efficiency
    }
}

void tas_unlock(TASLock* lock) {
    atomic_flag_clear_explicit(&lock->flag, memory_order_release);
}

// Test-and-Test-and-Set (TTAS) Spinlock - more cache-friendly
typedef struct {
    atomic_int locked;
} TTASLock;

void ttas_init(TTASLock* lock) {
    atomic_init(&lock->locked, 0);
}

void ttas_lock(TTASLock* lock) {
    while (1) {
        // First test (read-only, cache-friendly)
        while (atomic_load_explicit(&lock->locked, memory_order_relaxed)) {
            PAUSE();  // Reduce pipeline stalls
        }
        // Then try to acquire
        int expected = 0;
        if (atomic_compare_exchange_weak_explicit(&lock->locked, &expected, 1,
                memory_order_acquire, memory_order_relaxed)) {
            return;  // Got the lock
        }
    }
}

void ttas_unlock(TTASLock* lock) {
    atomic_store_explicit(&lock->locked, 0, memory_order_release);
}

// Spinlock with Exponential Backoff
typedef struct {
    atomic_int locked;
    int max_backoff;
} BackoffLock;

void backoff_init(BackoffLock* lock, int max_backoff) {
    atomic_init(&lock->locked, 0);
    lock->max_backoff = max_backoff;
}

static void do_backoff(int iterations) {
    for (volatile int i = 0; i < iterations; i++) {
        PAUSE();
    }
}

void backoff_lock(BackoffLock* lock) {
    int backoff = 1;
    while (1) {
        while (atomic_load_explicit(&lock->locked, memory_order_relaxed)) {
            PAUSE();
        }
        
        int expected = 0;
        if (atomic_compare_exchange_weak_explicit(&lock->locked, &expected, 1,
                memory_order_acquire, memory_order_relaxed)) {
            return;
        }
        
        // Failed, back off
        do_backoff(backoff);
        if (backoff < lock->max_backoff) {
            backoff *= 2;
        }
    }
}

void backoff_unlock(BackoffLock* lock) {
    atomic_store_explicit(&lock->locked, 0, memory_order_release);
}

// Ticket Lock - fair, FIFO ordering
typedef struct {
    atomic_uint next_ticket;
    atomic_uint now_serving;
} TicketLock;

void ticket_init(TicketLock* lock) {
    atomic_init(&lock->next_ticket, 0);
    atomic_init(&lock->now_serving, 0);
}

void ticket_lock(TicketLock* lock) {
    unsigned int my_ticket = atomic_fetch_add(&lock->next_ticket, 1);
    while (atomic_load(&lock->now_serving) != my_ticket) {
        PAUSE();
    }
}

void ticket_unlock(TicketLock* lock) {
    atomic_fetch_add(&lock->now_serving, 1);
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

TASLock tas_global;
TTASLock ttas_global;
TicketLock ticket_global;
int shared_counter = 0;

#ifndef _WIN32
void* tas_thread_func(void* arg) {
    for (int i = 0; i < 10000; i++) {
        tas_lock(&tas_global);
        shared_counter++;
        tas_unlock(&tas_global);
    }
    return NULL;
}
#endif

void test_tas_lock() {
    printf("Test: TAS Lock basic... ");
    TASLock lock;
    tas_init(&lock);
    
    tas_lock(&lock);
    // Critical section
    tas_unlock(&lock);
    
    printf("PASSED\n");
}

void test_ttas_lock() {
    printf("Test: TTAS Lock basic... ");
    TTASLock lock;
    ttas_init(&lock);
    
    ttas_lock(&lock);
    // Critical section
    ttas_unlock(&lock);
    
    printf("PASSED\n");
}

void test_ticket_lock() {
    printf("Test: Ticket Lock basic... ");
    TicketLock lock;
    ticket_init(&lock);
    
    ticket_lock(&lock);
    // Critical section
    ticket_unlock(&lock);
    
    printf("PASSED\n");
}

void test_backoff_lock() {
    printf("Test: Backoff Lock basic... ");
    BackoffLock lock;
    backoff_init(&lock, 1000);
    
    backoff_lock(&lock);
    // Critical section
    backoff_unlock(&lock);
    
    printf("PASSED\n");
}

#ifndef _WIN32
void test_multithreaded() {
    printf("Test: Multi-threaded TAS... ");
    tas_init(&tas_global);
    shared_counter = 0;
    
    pthread_t threads[4];
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, tas_thread_func, NULL);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    assert(shared_counter == 40000);
    printf("PASSED\n");
}
#endif

int main() {
    printf("=== Spinlock CAS Implementation Tests ===\n\n");
    test_tas_lock();
    test_ttas_lock();
    test_ticket_lock();
    test_backoff_lock();
#ifndef _WIN32
    test_multithreaded();
#endif
    printf("\nAll tests passed!\n");
    return 0;
}
