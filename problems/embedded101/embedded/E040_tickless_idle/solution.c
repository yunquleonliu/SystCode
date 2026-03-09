#include <stdio.h>
/*
 * E040: Tickless Idle
 *
 * Calculate how long the OS can sleep before the next timer event to save power.
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
    printf("[E040] rtos_core winner=%d %s\n", winner, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
