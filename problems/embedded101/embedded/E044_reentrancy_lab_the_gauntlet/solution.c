#include <stdio.h>
/*
 * E044: Reentrancy Lab The Gauntlet
 *
 * Create a driver that fails under preemption (race condition), then fix it using Mutex, Critical Sections, and Lock-Free methods.
 * First-pass implementation for batch rollout.
 */


typedef struct {
    int ready;
    int prio;
} Task;

static int pick_highest(Task* tasks, int count) {
    int best = -1;
    for (int i = 0; i < count; ++i) {
        if (!tasks[i].ready) continue;
        if (best < 0 || tasks[i].prio > tasks[best].prio) best = i;
    }
    return best;
}

int main(void) {
    Task tasks[4] = { {1, 1}, {1, 3}, {0, 9}, {1, 2} };
    int winner = pick_highest(tasks, 4);
    int ok = (winner == 1);
    printf("[E044] rtos_core winner=%d %s\n", winner, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
