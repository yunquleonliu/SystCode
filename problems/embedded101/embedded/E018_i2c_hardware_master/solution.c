#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint8_t regs[256];
} Sensor;

static void i2c_hw_write_reg(Sensor* sensor, uint8_t reg, uint8_t value) {
    sensor->regs[reg] = value;
}

static uint8_t i2c_hw_read_reg(const Sensor* sensor, uint8_t reg) {
    return sensor->regs[reg];
}

int main(void) {
    Sensor sensor = {0};
    i2c_hw_write_reg(&sensor, 0x10u, 0x3Cu);
    i2c_hw_write_reg(&sensor, 0x11u, 0x7Au);
    uint8_t a = i2c_hw_read_reg(&sensor, 0x10u);
    uint8_t b = i2c_hw_read_reg(&sensor, 0x11u);
    int ok = (a == 0x3Cu) && (b == 0x7Au);
    printf("[E018] reg10=0x%02X reg11=0x%02X %s\n", a, b, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
