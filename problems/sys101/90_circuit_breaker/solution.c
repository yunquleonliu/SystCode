/**
 * Problem 90: Circuit Breaker Pattern
 * Fault tolerance with fast-fail
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
    STATE_CLOSED,
    STATE_OPEN,
    STATE_HALF_OPEN
} CircuitState;

typedef struct {
    CircuitState state;
    int failure_count;
    int success_count;
    int failure_threshold;
    long last_state_change;
    int timeout_seconds;
} CircuitBreaker;

CircuitBreaker* breaker_create(int failure_threshold, int timeout) {
    CircuitBreaker* cb = malloc(sizeof(CircuitBreaker));
    cb->state = STATE_CLOSED;
    cb->failure_count = 0;
    cb->success_count = 0;
    cb->failure_threshold = failure_threshold;
    cb->timeout_seconds = timeout;
    cb->last_state_change = time(NULL);
    return cb;
}

int breaker_call(CircuitBreaker* cb, int success) {
    time_t now = time(NULL);
    
    switch (cb->state) {
        case STATE_CLOSED:
            if (success) {
                cb->failure_count = 0;
                return 1;
            } else {
                cb->failure_count++;
                if (cb->failure_count >= cb->failure_threshold) {
                    cb->state = STATE_OPEN;
                    cb->last_state_change = now;
                }
                return 0;
            }
            break;
            
        case STATE_OPEN:
            if (now - cb->last_state_change > cb->timeout_seconds) {
                cb->state = STATE_HALF_OPEN;
                cb->success_count = 0;
                return 0;  // Attempt recovery
            }
            return -1;  // Fast fail
            
        case STATE_HALF_OPEN:
            if (success) {
                cb->success_count++;
                if (cb->success_count >= 2) {
                    cb->state = STATE_CLOSED;
                    cb->failure_count = 0;
                }
                return 1;
            } else {
                cb->state = STATE_OPEN;
                cb->last_state_change = now;
                return 0;
            }
    }
    
    return 0;
}

void test_scenario() {
    printf("Running tests for Circuit Breaker...\n\n");
    
    CircuitBreaker* cb = breaker_create(3, 5);  // 3 failures = open, 5s timeout
    
    printf("Circuit Breaker Pattern Test:\n\n");
    
    // Fail 3 times
    printf("Failing 3 times...\n");
    for (int i = 0; i < 3; i++) {
        int result = breaker_call(cb, 0);
        printf("  Call %d: %s\n", i+1, result == 0 ? "Failed" : "Allowed");
    }
    
    printf("State: %s\n", cb->state == STATE_OPEN ? "OPEN" : "CLOSED");
    
    // Try call while open
    printf("\nAttempt call while OPEN...\n");
    int result = breaker_call(cb, 0);
    printf("Result: %s\n", result == -1 ? "Fast Fail" : "Allowed");
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}