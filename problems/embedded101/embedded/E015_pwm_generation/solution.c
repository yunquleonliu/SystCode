#include <stdio.h>

typedef struct {
    int period_ticks;
    int high_ticks;
} PwmConfig;

static int pwm_level(const PwmConfig* config, int tick) {
    int slot = tick % config->period_ticks;
    return slot < config->high_ticks;
}

int main(void) {
    PwmConfig pwm = {.period_ticks = 20, .high_ticks = 7};
    int high = 0;
    for (int tick = 0; tick < pwm.period_ticks; ++tick) {
        high += pwm_level(&pwm, tick);
    }
    int duty = (high * 100) / pwm.period_ticks;
    int ok = (duty == 35);
    printf("[E015] duty=%d%% %s\n", duty, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
