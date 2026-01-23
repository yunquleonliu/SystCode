/**
 * Problem 08: Thread Pool
 * Fixed-size worker thread pool with task queue.
 * Supports graceful shutdown.
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

static int pthread_create(pthread_t* t, void* attr, void* (*fn)(void*), void* arg) {
    *t = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)fn, arg, 0, NULL);
    return *t ? 0 : -1;
}
static int pthread_join(pthread_t t, void** ret) {
    WaitForSingleObject(t, INFINITE);
    CloseHandle(t);
    return 0;
}
#else
#include <pthread.h>
#include <unistd.h>
#endif

typedef void (*TaskFunc)(void* arg);

typedef struct Task {
    TaskFunc func;
    void* arg;
    struct Task* next;
} Task;

typedef struct {
    pthread_t* threads;
    int thread_count;
    
    Task* queue_head;
    Task* queue_tail;
    int queue_size;
    
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    
    bool shutdown;
    int max_queue_size;
} ThreadPool;

static void* worker_thread(void* arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    
    while (1) {
        pthread_mutex_lock(&pool->lock);
        
        while (pool->queue_size == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->not_empty, &pool->lock);
        }
        
        if (pool->shutdown && pool->queue_size == 0) {
            pthread_mutex_unlock(&pool->lock);
            break;
        }
        
        // Dequeue task
        Task* task = pool->queue_head;
        pool->queue_head = task->next;
        if (pool->queue_head == NULL) {
            pool->queue_tail = NULL;
        }
        pool->queue_size--;
        
        pthread_cond_signal(&pool->not_full);
        pthread_mutex_unlock(&pool->lock);
        
        // Execute task
        task->func(task->arg);
        free(task);
    }
    
    return NULL;
}

ThreadPool* threadpool_create(int thread_count, int max_queue) {
    ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
    if (!pool) return NULL;
    
    pool->threads = (pthread_t*)malloc(sizeof(pthread_t) * thread_count);
    pool->thread_count = thread_count;
    pool->queue_head = NULL;
    pool->queue_tail = NULL;
    pool->queue_size = 0;
    pool->shutdown = false;
    pool->max_queue_size = max_queue;
    
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->not_empty, NULL);
    pthread_cond_init(&pool->not_full, NULL);
    
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&pool->threads[i], NULL, worker_thread, pool);
    }
    
    return pool;
}

bool threadpool_submit(ThreadPool* pool, TaskFunc func, void* arg) {
    if (!pool || !func) return false;
    
    Task* task = (Task*)malloc(sizeof(Task));
    if (!task) return false;
    task->func = func;
    task->arg = arg;
    task->next = NULL;
    
    pthread_mutex_lock(&pool->lock);
    
    while (pool->queue_size >= pool->max_queue_size && !pool->shutdown) {
        pthread_cond_wait(&pool->not_full, &pool->lock);
    }
    
    if (pool->shutdown) {
        pthread_mutex_unlock(&pool->lock);
        free(task);
        return false;
    }
    
    // Enqueue
    if (pool->queue_tail) {
        pool->queue_tail->next = task;
    } else {
        pool->queue_head = task;
    }
    pool->queue_tail = task;
    pool->queue_size++;
    
    pthread_cond_signal(&pool->not_empty);
    pthread_mutex_unlock(&pool->lock);
    
    return true;
}

void threadpool_destroy(ThreadPool* pool) {
    if (!pool) return;
    
    pthread_mutex_lock(&pool->lock);
    pool->shutdown = true;
    pthread_cond_broadcast(&pool->not_empty);
    pthread_cond_broadcast(&pool->not_full);
    pthread_mutex_unlock(&pool->lock);
    
    for (int i = 0; i < pool->thread_count; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    
    // Free remaining tasks
    Task* task = pool->queue_head;
    while (task) {
        Task* next = task->next;
        free(task);
        task = next;
    }
    
    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->not_empty);
    pthread_cond_destroy(&pool->not_full);
    free(pool->threads);
    free(pool);
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

volatile int completed_tasks = 0;
pthread_mutex_t test_lock;

void test_task(void* arg) {
    int* val = (int*)arg;
    pthread_mutex_lock(&test_lock);
    completed_tasks += *val;
    pthread_mutex_unlock(&test_lock);
}

void test_basic_pool() {
    printf("Test: Basic thread pool... ");
    pthread_mutex_init(&test_lock, NULL);
    completed_tasks = 0;
    
    ThreadPool* pool = threadpool_create(4, 100);
    assert(pool != NULL);
    
    int values[10];
    for (int i = 0; i < 10; i++) {
        values[i] = 1;
        threadpool_submit(pool, test_task, &values[i]);
    }
    
    threadpool_destroy(pool);
    
    assert(completed_tasks == 10);
    pthread_mutex_destroy(&test_lock);
    printf("PASSED\n");
}

void heavy_task(void* arg) {
    volatile int sum = 0;
    for (int i = 0; i < 10000; i++) sum += i;
    (void)sum;
}

void test_heavy_load() {
    printf("Test: Heavy load... ");
    ThreadPool* pool = threadpool_create(4, 1000);
    
    for (int i = 0; i < 100; i++) {
        threadpool_submit(pool, heavy_task, NULL);
    }
    
    threadpool_destroy(pool);
    printf("PASSED\n");
}

int main() {
    printf("=== Thread Pool Tests ===\n\n");
    test_basic_pool();
    test_heavy_load();
    printf("\nAll tests passed!\n");
    return 0;
}
