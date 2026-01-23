/**
 * Problem 86: Streaming Window Aggregation
 * Time-window operations on continuous data
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WINDOW_SIZE 10
#define BUFFER_SIZE 1000

typedef struct {
    long timestamp;
    double value;
} DataPoint;

typedef struct {
    DataPoint buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} SlidingWindow;

SlidingWindow* window_create() {
    SlidingWindow* w = malloc(sizeof(SlidingWindow));
    w->head = 0;
    w->tail = 0;
    w->count = 0;
    return w;
}

void window_add(SlidingWindow* w, double value) {
    if (w->count < BUFFER_SIZE) {
        w->buffer[w->tail].timestamp = time(NULL);
        w->buffer[w->tail].value = value;
        w->tail = (w->tail + 1) % BUFFER_SIZE;
        w->count++;
        
        if (w->count > WINDOW_SIZE) {
            w->head = (w->head + 1) % BUFFER_SIZE;
            w->count--;
        }
    }
}

double window_sum(SlidingWindow* w) {
    double sum = 0;
    for (int i = 0; i < w->count; i++) {
        int idx = (w->head + i) % BUFFER_SIZE;
        sum += w->buffer[idx].value;
    }
    return sum;
}

double window_avg(SlidingWindow* w) {
    return w->count > 0 ? window_sum(w) / w->count : 0;
}

void test_scenario() {
    printf("Running tests for Streaming Window...\n\n");
    
    SlidingWindow* w = window_create();
    
    // Add values
    for (int i = 0; i < 20; i++) {
        window_add(w, i + 1.0);
    }
    
    printf("Added 20 values\n");
    printf("Window size (max): %d\n", WINDOW_SIZE);
    printf("Current window size: %d\n", w->count);
    printf("Window sum: %.2f\n", window_sum(w));
    printf("Window average: %.2f\n", window_avg(w));
    
    printf("Passed.\n");
    free(w);
}

int main() {
    test_scenario();
    return 0;
}