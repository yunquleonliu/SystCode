#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile uint32_t control;
} GpioRegister;

static void reg_set_bits(volatile uint32_t* reg, uint32_t mask) {
    *reg |= mask;
}

static void reg_clear_bits(volatile uint32_t* reg, uint32_t mask) {
    *reg &= ~mask;
}

static void reg_toggle_bits(volatile uint32_t* reg, uint32_t mask) {
    *reg ^= mask;
}

static uint32_t reg_read_bits(volatile uint32_t* reg, uint32_t mask) {
    return *reg & mask;
}

int main(void) {
    enum {
        GPIO_ENABLE = (1u << 0),
        GPIO_OUTPUT = (1u << 1),
        GPIO_PULLUP = (1u << 2)
    };

    GpioRegister gpio = {0};

    reg_set_bits(&gpio.control, GPIO_ENABLE | GPIO_OUTPUT);
    reg_toggle_bits(&gpio.control, GPIO_PULLUP);
    reg_clear_bits(&gpio.control, GPIO_OUTPUT);

    int ok = (reg_read_bits(&gpio.control, GPIO_ENABLE) != 0u) &&
             (reg_read_bits(&gpio.control, GPIO_OUTPUT) == 0u) &&
             (reg_read_bits(&gpio.control, GPIO_PULLUP) != 0u);

    printf("[E004] reg=0x%08X %s\n", gpio.control, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
