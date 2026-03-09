#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t counter;
    uint32_t period;
    uint32_t events;
} Timer;

static void timer_tick(Timer* timer) {
    timer->counter++;
    if (timer->counter >= timer->period) {
        timer->counter = 0;
        timer->events++;
    }
}

int main(void) {
    Timer timer = {.counter = 0, .period = 5, .events = 0};
    for (int index = 0; index < 23; ++index) {
        timer_tick(&timer);
    }
    int ok = (timer.events == 4u) && (timer.counter == 3u);
    printf("[E014] events=%u counter=%u %s\n", timer.events, timer.counter, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
