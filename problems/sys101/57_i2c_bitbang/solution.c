/**
 * Problem 57: I2C Bit-Banging Protocol
 * I2C communication via GPIO bit manipulation.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sda;  // Serial Data line
    int scl;  // Serial Clock line
} I2CBus;

I2CBus* i2c_init() {
    I2CBus* bus = malloc(sizeof(I2CBus));
    bus->sda = 1;
    bus->scl = 1;
    printf("I2C bus initialized (SDA=1, SCL=1)\n");
    return bus;
}

void i2c_start(I2CBus* bus) {
    bus->sda = 0;
    printf("START: SDA=0\n");
}

void i2c_stop(I2CBus* bus) {
    bus->sda = 1;
    printf("STOP: SDA=1\n");
}

void i2c_write_bit(I2CBus* bus, int bit) {
    bus->sda = bit;
    bus->scl = 1;
    printf("Write bit %d\n", bit);
    bus->scl = 0;
}

int i2c_read_bit(I2CBus* bus) {
    bus->scl = 1;
    int bit = bus->sda;
    bus->scl = 0;
    printf("Read bit %d\n", bit);
    return bit;
}

int main() {
    printf("=== I2C Bit-Banging ===\n\n");
    I2CBus* bus = i2c_init();
    i2c_start(bus);
    i2c_write_bit(bus, 1);
    i2c_write_bit(bus, 0);
    i2c_write_bit(bus, 1);
    i2c_stop(bus);
    free(bus);
    return 0;
}