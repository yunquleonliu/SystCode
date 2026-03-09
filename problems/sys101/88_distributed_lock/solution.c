/**
 * Problem 88: Distributed Mutual Exclusion
 * Lock coordination across systems
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    int owner;
    long acquire_time;
    int locked;
    pthread_mutex_t mutex;
} DistributedLock;

typedef struct {
    DistributedLock locks[10];
} LockManager;

LockManager* lockman_create() {
    LockManager* lm = malloc(sizeof(LockManager));
    for (int i = 0; i < 10; i++) {
        lm->locks[i].owner = -1;
        lm->locks[i].locked = 0;
        pthread_mutex_init(&lm->locks[i].mutex, NULL);
    }
    return lm;
}

int lockman_acquire(LockManager* lm, int lock_id, int process_id) {
    pthread_mutex_lock(&lm->locks[lock_id].mutex);
    
    if (!lm->locks[lock_id].locked) {
        lm->locks[lock_id].locked = 1;
        lm->locks[lock_id].owner = process_id;
        lm->locks[lock_id].acquire_time = time(NULL);
        
        pthread_mutex_unlock(&lm->locks[lock_id].mutex);
        return 1;  // Success
    }
    
    pthread_mutex_unlock(&lm->locks[lock_id].mutex);
    return 0;  // Conflict
}

void lockman_release(LockManager* lm, int lock_id) {
    pthread_mutex_lock(&lm->locks[lock_id].mutex);
    
    lm->locks[lock_id].locked = 0;
    lm->locks[lock_id].owner = -1;
    
    pthread_mutex_unlock(&lm->locks[lock_id].mutex);
}

void test_scenario() {
    printf("Running tests for Distributed Lock...\n\n");
    
    LockManager* lm = lockman_create();
    
    // Process 1 acquires lock
    if (lockman_acquire(lm, 0, 1)) {
        printf("Process 1 acquired lock 0\n");
    }
    
    // Process 2 tries to acquire same lock
    if (!lockman_acquire(lm, 0, 2)) {
        printf("Process 2 blocked on lock 0\n");
    }
    
    // Process 1 releases
    lockman_release(lm, 0);
    printf("Process 1 released lock 0\n");
    
    // Now process 2 can acquire
    if (lockman_acquire(lm, 0, 2)) {
        printf("Process 2 acquired lock 0\n");
    }
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}