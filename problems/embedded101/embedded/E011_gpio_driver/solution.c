#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t dir;
    uint32_t out;
    uint32_t in;
} Gpio;

static void gpio_set_output(Gpio* gpio, int pin) { gpio->dir |= (1u << pin); }
static void gpio_set_input(Gpio* gpio, int pin) { gpio->dir &= ~(1u << pin); }
static void gpio_write(Gpio* gpio, int pin, int value) {
    if ((gpio->dir & (1u << pin)) == 0u) return;
    if (value) gpio->out |= (1u << pin); else gpio->out &= ~(1u << pin);
}
static void gpio_toggle(Gpio* gpio, int pin) { gpio->out ^= (1u << pin); }
static int gpio_read(const Gpio* gpio, int pin) {
    if (gpio->dir & (1u << pin)) return (gpio->out >> pin) & 1u;
    return (gpio->in >> pin) & 1u;
}

int main(void) {
    Gpio gpio = {0};
    gpio_set_output(&gpio, 3);
    gpio_set_input(&gpio, 4);
    gpio_write(&gpio, 3, 1);
    gpio.in |= (1u << 4);
    gpio_toggle(&gpio, 3);

    int ok = (gpio_read(&gpio, 3) == 0) && (gpio_read(&gpio, 4) == 1);
    printf("[E011] dir=0x%X out=0x%X in=0x%X %s\n", gpio.dir, gpio.out, gpio.in, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
