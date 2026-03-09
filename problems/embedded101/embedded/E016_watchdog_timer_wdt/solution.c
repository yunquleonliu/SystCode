#include <stdio.h>

typedef struct {
    int timeout_ticks;
    int counter;
    int resets;
} Watchdog;

static void wdt_tick(Watchdog* wdt) {
    wdt->counter++;
    if (wdt->counter >= wdt->timeout_ticks) {
        wdt->resets++;
        wdt->counter = 0;
    }
}

static void wdt_kick(Watchdog* wdt) {
    wdt->counter = 0;
}

int main(void) {
    Watchdog wdt = {.timeout_ticks = 4, .counter = 0, .resets = 0};
    wdt_tick(&wdt);
    wdt_tick(&wdt);
    wdt_kick(&wdt);
    wdt_tick(&wdt);
    wdt_tick(&wdt);
    wdt_tick(&wdt);
    wdt_tick(&wdt);
    int ok = (wdt.resets == 1);
    printf("[E016] resets=%d %s\n", wdt.resets, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
