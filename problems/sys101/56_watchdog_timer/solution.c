/**
 * Problem 56: Watchdog Timer
 * System watchdog and reset mechanism.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    time_t start_time;
    int timeout_sec;
    int pet_count;
    int triggered;
} Watchdog;

Watchdog* watchdog_init(int timeout) {
    Watchdog* wd = malloc(sizeof(Watchdog));
    wd->start_time = time(NULL);
    wd->timeout_sec = timeout;
    wd->pet_count = 0;
    wd->triggered = 0;
    printf("Watchdog initialized (timeout=%d sec)\n", timeout);
    return wd;
}

void watchdog_pet(Watchdog* wd) {
    wd->start_time = time(NULL);
    wd->pet_count++;
    printf("Watchdog petted (#%d)\n", wd->pet_count);
}

int watchdog_check(Watchdog* wd) {
    time_t elapsed = time(NULL) - wd->start_time;
    if (elapsed > wd->timeout_sec) {
        wd->triggered = 1;
        printf("Watchdog TRIGGERED! System reset!\n");
        return 1;
    }
    return 0;
}

int main() {
    printf("=== Watchdog Timer ===\n\n");
    Watchdog* wd = watchdog_init(5);
    watchdog_pet(wd);
    printf("Not expired\n");
    watchdog_pet(wd);
    watchdog_check(wd);
    free(wd);
    return 0;
}