#include <stdio.h>

typedef struct {
    int scl;
    int sda;
    int transitions;
} I2CBus;

static void set_scl(I2CBus* bus, int level) {
    if (bus->scl != level) bus->transitions++;
    bus->scl = level;
}

static void set_sda(I2CBus* bus, int level) {
    if (bus->sda != level) bus->transitions++;
    bus->sda = level;
}

static void i2c_start(I2CBus* bus) {
    set_sda(bus, 1); set_scl(bus, 1);
    set_sda(bus, 0); set_scl(bus, 0);
}

static void i2c_stop(I2CBus* bus) {
    set_sda(bus, 0); set_scl(bus, 1);
    set_sda(bus, 1);
}

static void i2c_write_byte(I2CBus* bus, unsigned value) {
    for (int bit = 7; bit >= 0; --bit) {
        set_sda(bus, (value >> bit) & 1u);
        set_scl(bus, 1);
        set_scl(bus, 0);
    }
    set_sda(bus, 1);
    set_scl(bus, 1);
    set_scl(bus, 0);
}

int main(void) {
    I2CBus bus = {.scl = 1, .sda = 1, .transitions = 0};
    i2c_start(&bus);
    i2c_write_byte(&bus, 0xA5u);
    i2c_stop(&bus);
    int ok = (bus.scl == 1) && (bus.sda == 1) && (bus.transitions > 20);
    printf("[E017] transitions=%d %s\n", bus.transitions, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
