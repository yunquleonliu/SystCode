/**
 * Problem 21: Two-Phase Commit Protocol
 * Distributed transaction coordination ensuring atomicity.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum { INIT, PREPARED, COMMITTED, ABORTED } TxState;

typedef struct {
    int id;
    TxState state;
    bool vote;  // true = YES, false = NO
} Participant;

typedef struct {
    int tx_id;
    TxState state;
    Participant* participants;
    int num_participants;
} Coordinator;

void coordinator_init(Coordinator* c, int tx_id, int num_participants) {
    c->tx_id = tx_id;
    c->state = INIT;
    c->num_participants = num_participants;
    c->participants = calloc(num_participants, sizeof(Participant));
    for (int i = 0; i < num_participants; i++) {
        c->participants[i].id = i;
        c->participants[i].state = INIT;
    }
}

// Phase 1: Prepare - Ask all participants to prepare
bool coordinator_prepare(Coordinator* c) {
    printf("Coordinator: Starting PREPARE phase for TX %d\n", c->tx_id);
    
    bool all_yes = true;
    for (int i = 0; i < c->num_participants; i++) {
        Participant* p = &c->participants[i];
        // Simulate participant decision (random or always yes for demo)
        p->vote = true;  // Participant votes YES
        p->state = PREPARED;
        printf("  Participant %d: VOTE %s\n", p->id, p->vote ? "YES" : "NO");
        if (!p->vote) all_yes = false;
    }
    
    c->state = PREPARED;
    return all_yes;
}

// Phase 2: Commit or Abort
void coordinator_commit(Coordinator* c) {
    printf("Coordinator: COMMIT TX %d\n", c->tx_id);
    for (int i = 0; i < c->num_participants; i++) {
        c->participants[i].state = COMMITTED;
        printf("  Participant %d: COMMITTED\n", i);
    }
    c->state = COMMITTED;
}

void coordinator_abort(Coordinator* c) {
    printf("Coordinator: ABORT TX %d\n", c->tx_id);
    for (int i = 0; i < c->num_participants; i++) {
        c->participants[i].state = ABORTED;
        printf("  Participant %d: ABORTED\n", i);
    }
    c->state = ABORTED;
}

void two_phase_commit(Coordinator* c) {
    if (coordinator_prepare(c)) {
        coordinator_commit(c);
    } else {
        coordinator_abort(c);
    }
}

void coordinator_free(Coordinator* c) {
    free(c->participants);
}

int main() {
    printf("=== Two-Phase Commit Protocol ===\n\n");
    
    Coordinator c;
    coordinator_init(&c, 1001, 3);
    two_phase_commit(&c);
    coordinator_free(&c);
    
    printf("\nTransaction completed.\n");
    return 0;
}