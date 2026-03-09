/**
 * Problem 09: Read-Write Lock (Writer Preferring)
 * Multiple readers OR one writer. Writers have priority.
 * Prevents writer starvation.
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
#define pthread_cond_signal(c) WakeConditionVariable(c)
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
    pthread_cond_t readers_cv;
    pthread_cond_t writers_cv;
    
    int readers_active;      // Count of readers currently reading
    int readers_waiting;     // Count of readers waiting
    int writers_active;      // 0 or 1
    int writers_waiting;     // Count of writers waiting
} RWLock;

void rwlock_init(RWLock* lock) {
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->readers_cv, NULL);
    pthread_cond_init(&lock->writers_cv, NULL);
    lock->readers_active = 0;
    lock->readers_waiting = 0;
    lock->writers_active = 0;
    lock->writers_waiting = 0;
}

void rwlock_destroy(RWLock* lock) {
    pthread_mutex_destroy(&lock->mutex);
    pthread_cond_destroy(&lock->readers_cv);
    pthread_cond_destroy(&lock->writers_cv);
}

void rwlock_read_lock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    
    lock->readers_waiting++;
    // Wait if there's an active writer OR waiting writers (writer preference)
    while (lock->writers_active > 0 || lock->writers_waiting > 0) {
        pthread_cond_wait(&lock->readers_cv, &lock->mutex);
    }
    lock->readers_waiting--;
    lock->readers_active++;
    
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_read_unlock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    
    lock->readers_active--;
    if (lock->readers_active == 0 && lock->writers_waiting > 0) {
        pthread_cond_signal(&lock->writers_cv);
    }
    
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_lock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    
    lock->writers_waiting++;
    while (lock->readers_active > 0 || lock->writers_active > 0) {
        pthread_cond_wait(&lock->writers_cv, &lock->mutex);
    }
    lock->writers_waiting--;
    lock->writers_active = 1;
    
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_unlock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    
    lock->writers_active = 0;
    
    // Prefer writers: signal waiting writer first
    if (lock->writers_waiting > 0) {
        pthread_cond_signal(&lock->writers_cv);
    } else {
        pthread_cond_broadcast(&lock->readers_cv);
    }
    
    pthread_mutex_unlock(&lock->mutex);
}

// Try-lock variants
bool rwlock_try_read_lock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    if (lock->writers_active > 0 || lock->writers_waiting > 0) {
        pthread_mutex_unlock(&lock->mutex);
        return false;
    }
    lock->readers_active++;
    pthread_mutex_unlock(&lock->mutex);
    return true;
}

bool rwlock_try_write_lock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    if (lock->readers_active > 0 || lock->writers_active > 0) {
        pthread_mutex_unlock(&lock->mutex);
        return false;
    }
    lock->writers_active = 1;
    pthread_mutex_unlock(&lock->mutex);
    return true;
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

RWLock global_rwlock;
volatile int shared_data = 0;

void test_basic_read_write() {
    printf("Test: Basic read/write lock... ");
    RWLock lock;
    rwlock_init(&lock);
    
    rwlock_read_lock(&lock);
    // Read operation
    rwlock_read_unlock(&lock);
    
    rwlock_write_lock(&lock);
    // Write operation
    rwlock_write_unlock(&lock);
    
    rwlock_destroy(&lock);
    printf("PASSED\n");
}

void test_multiple_readers() {
    printf("Test: Multiple concurrent readers... ");
    RWLock lock;
    rwlock_init(&lock);
    
    // Multiple read locks should be allowed
    rwlock_read_lock(&lock);
    assert(rwlock_try_read_lock(&lock));  // Should succeed
    
    rwlock_read_unlock(&lock);
    rwlock_read_unlock(&lock);
    
    rwlock_destroy(&lock);
    printf("PASSED\n");
}

void test_writer_exclusion() {
    printf("Test: Writer exclusion... ");
    RWLock lock;
    rwlock_init(&lock);
    
    rwlock_write_lock(&lock);
    assert(!rwlock_try_read_lock(&lock));   // Should fail
    assert(!rwlock_try_write_lock(&lock));  // Should fail
    rwlock_write_unlock(&lock);
    
    rwlock_destroy(&lock);
    printf("PASSED\n");
}

void test_reader_blocks_writer() {
    printf("Test: Reader blocks writer... ");
    RWLock lock;
    rwlock_init(&lock);
    
    rwlock_read_lock(&lock);
    assert(!rwlock_try_write_lock(&lock));  // Should fail
    rwlock_read_unlock(&lock);
    
    assert(rwlock_try_write_lock(&lock));  // Should succeed now
    rwlock_write_unlock(&lock);
    
    rwlock_destroy(&lock);
    printf("PASSED\n");
}

int main() {
    printf("=== Read-Write Lock Tests ===\n\n");
    test_basic_read_write();
    test_multiple_readers();
    test_writer_exclusion();
    test_reader_blocks_writer();
    printf("\nAll tests passed!\n");
    return 0;
}
