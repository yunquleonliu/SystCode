/**
 * Problem 23: Vector Clock
 * Track causality in distributed systems.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NODES 5

typedef struct {
    int clock[MAX_NODES];
    int node_id;
    int num_nodes;
} VectorClock;

void vc_init(VectorClock* vc, int node_id, int num_nodes) {
    memset(vc->clock, 0, sizeof(vc->clock));
    vc->node_id = node_id;
    vc->num_nodes = num_nodes;
}

// Local event: increment own counter
void vc_tick(VectorClock* vc) {
    vc->clock[vc->node_id]++;
}

// Sending: tick then return copy
void vc_send(VectorClock* vc, int* out_clock) {
    vc_tick(vc);
    memcpy(out_clock, vc->clock, sizeof(vc->clock));
}

// Receiving: merge and tick
void vc_receive(VectorClock* vc, const int* received_clock) {
    for (int i = 0; i < vc->num_nodes; i++) {
        if (received_clock[i] > vc->clock[i]) {
            vc->clock[i] = received_clock[i];
        }
    }
    vc_tick(vc);
}

// Compare: -1 if a < b, 1 if a > b, 0 if concurrent
int vc_compare(const int* a, const int* b, int n) {
    bool a_less = false, b_less = false;
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) a_less = true;
        if (a[i] > b[i]) b_less = true;
    }
    if (a_less && !b_less) return -1;  // a happened before b
    if (b_less && !a_less) return 1;   // b happened before a
    return 0;  // concurrent
}

void vc_print(const char* label, VectorClock* vc) {
    printf("%s [", label);
    for (int i = 0; i < vc->num_nodes; i++) {
        printf("%d%s", vc->clock[i], i < vc->num_nodes - 1 ? ", " : "");
    }
    printf("]\n");
}

int main() {
    printf("=== Vector Clock ===\n\n");
    
    VectorClock vc_a, vc_b, vc_c;
    vc_init(&vc_a, 0, 3);
    vc_init(&vc_b, 1, 3);
    vc_init(&vc_c, 2, 3);
    
    int msg[MAX_NODES];
    
    // A does local event
    vc_tick(&vc_a);
    vc_print("A after local event:", &vc_a);
    
    // A sends to B
    vc_send(&vc_a, msg);
    vc_receive(&vc_b, msg);
    vc_print("B after receiving from A:", &vc_b);
    
    // B does local event
    vc_tick(&vc_b);
    vc_print("B after local event:", &vc_b);
    
    // B sends to C
    vc_send(&vc_b, msg);
    vc_receive(&vc_c, msg);
    vc_print("C after receiving from B:", &vc_c);
    
    // Compare A and C
    int cmp = vc_compare(vc_a.clock, vc_c.clock, 3);
    printf("\nA vs C: %s\n", cmp < 0 ? "A happened before C" : 
                               cmp > 0 ? "C happened before A" : "Concurrent");
    
    return 0;
}