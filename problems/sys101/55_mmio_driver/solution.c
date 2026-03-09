/**
 * Problem 55: Memory-Mapped I/O (MMIO) Driver
 * Hardware register access via memory mapping.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    volatile uint32_t control;
    volatile uint32_t status;
    volatile uint32_t data;
    volatile uint32_t interrupt;
} HardwareRegs;

typedef struct {
    HardwareRegs* regs;
    uint32_t base_addr;
} MMIODriver;

MMIODriver* mmio_init(uint32_t base_addr) {
    MMIODriver* drv = malloc(sizeof(MMIODriver));
    drv->base_addr = base_addr;
    drv->regs = (HardwareRegs*)(uintptr_t)base_addr;
    printf("MMIO driver initialized @ 0x%x\n", base_addr);
    return drv;
}

void mmio_write_reg(MMIODriver* drv, uint32_t offset, uint32_t value) {
    volatile uint32_t* reg = (volatile uint32_t*)(uintptr_t)(drv->base_addr + offset);
    *reg = value;
    printf("MMIO write [0x%x] = 0x%x\n", drv->base_addr + offset, value);
}

uint32_t mmio_read_reg(MMIODriver* drv, uint32_t offset) {
    volatile uint32_t* reg = (volatile uint32_t*)(uintptr_t)(drv->base_addr + offset);
    uint32_t value = *reg;
    printf("MMIO read [0x%x] = 0x%x\n", drv->base_addr + offset, value);
    return value;
}

int main() {
    printf("=== MMIO Driver ===\n\n");
    uint8_t* fake_mem = calloc(4096, 1);
    MMIODriver* drv = mmio_init((uint32_t)(uintptr_t)fake_mem);
    mmio_write_reg(drv, 0, 0x12345678);
    mmio_read_reg(drv, 0);
    free(fake_mem);
    free(drv);
    return 0;
}