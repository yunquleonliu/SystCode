#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>

// --- Simulated Hardware ---------------------------------------------------
#define UART_BUFFER_SIZE 128
#define PREEMPTION_CHANCE 50 // % chance to yield in critical section

// This represents a hardware UART transmit FIFO buffer (not reentrant!)
typedef struct {
    char data[UART_BUFFER_SIZE];
    volatile int head;
    volatile int tail;
} UART_HW;

static UART_HW g_uart_regs = {.head = 0, .tail = 0};

// Mock function to simulate "writing to hardware" with potential preemption
void hw_transmit_byte(char byte) {
    // 1. Check if FIFO full (simplified)
    if (g_uart_regs.head >= UART_BUFFER_SIZE) {
        g_uart_regs.head = 0; // Wrap around for simulation
    }

    // 2. Simulate preemption/interrupt here!
    // This is the CRITICAL timing window for race conditions.
    if ((rand() % 100) < PREEMPTION_CHANCE) {
        usleep(100); // Allow another thread to run
    }

    // 3. Write to "register"
    g_uart_regs.data[g_uart_regs.head++] = byte;
    
    // Simulate slow hardware drain (so logs interleave)
    putchar(byte); 
    fflush(stdout);
}

// --- The Unsafe Driver ----------------------------------------------------

// Unsafe Implementation: Multiple threads calling this WILL corrupt data.
void uart_write_unsafe(const char* str) {
    // Shared global buffer index/pointer usage without locking
    // In a real embedded system, this might be a static local buffer
    // or direct access to `g_uart_regs` without synchronization.
    
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        hw_transmit_byte(str[i]);
    }
}

// --- Your Solutions -------------------------------------------------------

/* 
   TODO 1: Implement a version using a Mutex (Task-to-Task safety).
   Blocks the caller until the resource is free.
*/
pthread_mutex_t g_uart_mutex = PTHREAD_MUTEX_INITIALIZER;

void uart_write_mutex(const char* str) {
    // Your code here...
    uart_write_unsafe(str); // Replace with locked version
}

/* 
   TODO 2: Implement a version using Critical Sections (Task-to-ISR safety).
   Simulated by disabling "interrupts" (or a global spinlock flag).
   Typically involves __disable_irq() / __enable_irq().
*/
atomic_flag g_irq_lock = ATOMIC_FLAG_INIT;

void enter_critical() {
    // Spin until lock acquired (simulates disabling interrupts on single core)
    while (atomic_flag_test_and_set(&g_irq_lock)) {
        // In real hardware: __asm("cpsid i");
    }
}

void exit_critical() {
    atomic_flag_clear(&g_irq_lock);
    // In real hardware: __asm("cpsie i");
}

void uart_write_critical(const char* str) {
    // Your code here...
    uart_write_unsafe(str); 
}

/* 
   TODO 3: Implement a Reentrant / Lock-Free version.
   Avoids shared state entirely or uses atomic operations.
   Hint: Does the hardware *need* a software copy buffer? 
   Can we write directly from the user's stack buffer?
*/
void uart_write_reentrant(const char* str) {
    // Your code here...
    // Direct hardware write? Or per-thread buffer?
    uart_write_unsafe(str);
}


// --- Test Harness ---------------------------------------------------------

void* worker_thread(void* arg) {
    int id = *(int*)arg;
    char msg[64];
    snprintf(msg, sizeof(msg), "[Thread %d: Hello World %d]\n", id, id);

    for (int i = 0; i < 5; i++) {
        // Change this function call to test your implementations
        // uart_write_unsafe(msg);
        uart_write_mutex(msg); 
        // uart_write_critical(msg);
        usleep(1000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1, t2, t3;
    int id1=1, id2=2, id3=3;

    printf("Starting Reentrancy Lab...\n");
    printf("Expected: Clean lines like [Thread N: ...]\n");
    printf("Actual (Unsafe): Interleaved garbage like [Thr[Thread ead 1: ...]\n\n");

    pthread_create(&t1, NULL, worker_thread, &id1);
    pthread_create(&t2, NULL, worker_thread, &id2);
    pthread_create(&t3, NULL, worker_thread, &id3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nDone.\n");
    return 0;
}
