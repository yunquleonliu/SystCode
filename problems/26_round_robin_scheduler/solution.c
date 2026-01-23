/**
 * Problem 26: Round Robin Scheduler
 * Time-slice based process scheduling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PROCESSES 10

typedef enum { READY, RUNNING, BLOCKED, TERMINATED } ProcessState;

typedef struct {
    int pid;
    char name[32];
    ProcessState state;
    int remaining_time;
    int arrival_time;
    int wait_time;
    int turnaround_time;
} Process;

typedef struct {
    Process* queue[MAX_PROCESSES];
    int front, rear, size;
} ReadyQueue;

void queue_init(ReadyQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

void queue_enqueue(ReadyQueue* q, Process* p) {
    if (q->size >= MAX_PROCESSES) return;
    q->rear = (q->rear + 1) % MAX_PROCESSES;
    q->queue[q->rear] = p;
    q->size++;
}

Process* queue_dequeue(ReadyQueue* q) {
    if (q->size == 0) return NULL;
    Process* p = q->queue[q->front];
    q->front = (q->front + 1) % MAX_PROCESSES;
    q->size--;
    return p;
}

bool queue_empty(ReadyQueue* q) {
    return q->size == 0;
}

void schedule_round_robin(Process* processes, int n, int time_quantum) {
    ReadyQueue ready;
    queue_init(&ready);
    
    int current_time = 0;
    int completed = 0;
    
    // Initially add all processes
    for (int i = 0; i < n; i++) {
        processes[i].state = READY;
        queue_enqueue(&ready, &processes[i]);
    }
    
    printf("Time Quantum: %d\n\n", time_quantum);
    printf("Time | Process | Remaining\n");
    printf("-----|---------|----------\n");
    
    while (completed < n) {
        if (queue_empty(&ready)) {
            current_time++;
            continue;
        }
        
        Process* current = queue_dequeue(&ready);
        current->state = RUNNING;
        
        int run_time = (current->remaining_time < time_quantum) ? 
                        current->remaining_time : time_quantum;
        
        printf("%4d | %-7s | %d -> %d\n", current_time, current->name, 
               current->remaining_time, current->remaining_time - run_time);
        
        current->remaining_time -= run_time;
        current_time += run_time;
        
        // Update wait times for others
        for (int i = 0; i < ready.size; i++) {
            int idx = (ready.front + i) % MAX_PROCESSES;
            ready.queue[idx]->wait_time += run_time;
        }
        
        if (current->remaining_time > 0) {
            current->state = READY;
            queue_enqueue(&ready, current);
        } else {
            current->state = TERMINATED;
            current->turnaround_time = current_time - current->arrival_time;
            completed++;
            printf("     | %-7s | DONE (TAT=%d, WT=%d)\n", current->name, 
                   current->turnaround_time, current->wait_time);
        }
    }
}

int main() {
    printf("=== Round Robin Scheduler ===\n\n");
    
    Process processes[] = {
        {1, "P1", READY, 10, 0, 0, 0},
        {2, "P2", READY, 5, 0, 0, 0},
        {3, "P3", READY, 8, 0, 0, 0},
    };
    
    schedule_round_robin(processes, 3, 3);
    
    printf("\n--- Statistics ---\n");
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < 3; i++) {
        avg_tat += processes[i].turnaround_time;
        avg_wt += processes[i].wait_time;
    }
    printf("Avg Turnaround: %.2f\n", avg_tat / 3);
    printf("Avg Wait Time: %.2f\n", avg_wt / 3);
    
    return 0;
}