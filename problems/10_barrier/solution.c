/**
 * Problem 10: Thread Barrier
 * Synchronization point where N threads wait for each other.
 * Reusable for multiple phases.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
typedef HANDLE pthread_t;
typedef CRITICAL_SECTION pthread_mutex_t;
typedef CONDITION_VARIABLE pthread_cond_t;
#define pthread_mutex_init(m, a) InitializeCriticalSection(m)
#define pthread_mutex_destroy(m) DeleteCriticalSection(m)
#define pthread_mutex_lock(m) EnterCriticalSection(m)
#define pthread_mutex_unlock(m) LeaveCriticalSection(m)
#define pthread_cond_init(c, a) InitializeConditionVariable(c)
#define pthread_cond_destroy(c) ((void)0)
#define pthread_cond_wait(c, m) SleepConditionVariableCS(c, m, INFINITE)
#define pthread_cond_broadcast(c) WakeAllConditionVariable(c)
static int pthread_create(pthread_t* t, void* a, void* (*fn)(void*), void* arg) {
    *t = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)fn, arg, 0, NULL);
    return *t ? 0 : -1;
}
static int pthread_join(pthread_t t, void** r) {
    WaitForSingleObject(t, INFINITE); CloseHandle(t); return 0;
}
#else
#include <pthread.h>
#endif

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int threshold;       // Number of threads to wait for
    int count;           // Current waiting count
    int generation;      // For reusability - tracks barrier rounds
} Barrier;

void barrier_init(Barrier* b, int count) {
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
    b->threshold = count;
    b->count = 0;
    b->generation = 0;
}

void barrier_destroy(Barrier* b) {
    pthread_mutex_destroy(&b->mutex);
    pthread_cond_destroy(&b->cond);
}

// Returns true for exactly one thread (the "leader")
bool barrier_wait(Barrier* b) {
    pthread_mutex_lock(&b->mutex);
    
    int my_generation = b->generation;
    b->count++;
    
    if (b->count == b->threshold) {
        // Last thread to arrive
        b->count = 0;
        b->generation++;  // Move to next generation for reusability
        pthread_cond_broadcast(&b->cond);
        pthread_mutex_unlock(&b->mutex);
        return true;  // This thread is the "leader"
    }
    
    // Wait until generation changes
    while (my_generation == b->generation) {
        pthread_cond_wait(&b->cond, &b->mutex);
    }
    
    pthread_mutex_unlock(&b->mutex);
    return false;
}

// Sense-reversing barrier (more efficient for repeated use)
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int threshold;
    int count;
    bool sense;  // Global sense
} SenseBarrier;

void sense_barrier_init(SenseBarrier* b, int count) {
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
    b->threshold = count;
    b->count = 0;
    b->sense = false;
}

void sense_barrier_destroy(SenseBarrier* b) {
    pthread_mutex_destroy(&b->mutex);
    pthread_cond_destroy(&b->cond);
}

// Thread-local sense (in practice, use __thread or thread_local)
static bool local_sense = true;

void sense_barrier_wait(SenseBarrier* b) {
    local_sense = !local_sense;
    
    pthread_mutex_lock(&b->mutex);
    b->count++;
    
    if (b->count == b->threshold) {
        b->count = 0;
        b->sense = local_sense;
        pthread_cond_broadcast(&b->cond);
    } else {
        while (b->sense != local_sense) {
            pthread_cond_wait(&b->cond, &b->mutex);
        }
    }
    
    pthread_mutex_unlock(&b->mutex);
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

Barrier global_barrier;
volatile int phase_counter = 0;

void* barrier_thread(void* arg) {
    long id = (long)arg;
    
    // Phase 1
    printf("Thread %ld: Phase 1 starting\n", id);
    barrier_wait(&global_barrier);
    
    // Phase 2
    printf("Thread %ld: Phase 2 starting\n", id);
    barrier_wait(&global_barrier);
    
    printf("Thread %ld: Complete\n", id);
    return NULL;
}

void test_basic_barrier() {
    printf("Test: Basic barrier... ");
    Barrier b;
    barrier_init(&b, 1);
    
    bool is_leader = barrier_wait(&b);
    assert(is_leader);  // Only thread, so must be leader
    
    barrier_destroy(&b);
    printf("PASSED\n");
}

void test_reusable_barrier() {
    printf("Test: Reusable barrier... ");
    Barrier b;
    barrier_init(&b, 1);
    
    // Use barrier multiple times
    for (int i = 0; i < 5; i++) {
        barrier_wait(&b);
    }
    
    barrier_destroy(&b);
    printf("PASSED\n");
}

void test_multithreaded_barrier() {
    printf("Test: Multi-threaded barrier...\n");
    
    int num_threads = 4;
    barrier_init(&global_barrier, num_threads);
    
    pthread_t threads[4];
    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, barrier_thread, (void*)i);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    barrier_destroy(&global_barrier);
    printf("PASSED\n");
}

void test_sense_barrier() {
    printf("Test: Sense-reversing barrier... ");
    SenseBarrier b;
    sense_barrier_init(&b, 1);
    
    for (int i = 0; i < 5; i++) {
        sense_barrier_wait(&b);
    }
    
    sense_barrier_destroy(&b);
    printf("PASSED\n");
}

int main() {
    printf("=== Thread Barrier Tests ===\n\n");
    test_basic_barrier();
    test_reusable_barrier();
    test_sense_barrier();
    test_multithreaded_barrier();
    printf("\nAll tests passed!\n");
    return 0;
}
