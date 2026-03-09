#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint32_t read_u32_unaligned(const void* ptr) {
    uint32_t value;
    memcpy(&value, ptr, sizeof(value));
    return value;
}

static void write_u32_unaligned(void* ptr, uint32_t value) {
    memcpy(ptr, &value, sizeof(value));
}

int main(void) {
    uint8_t buffer[16] = {0};
    void* misaligned = &buffer[1];

    write_u32_unaligned(misaligned, 0xDEADBEEFu);
    uint32_t value = read_u32_unaligned(misaligned);
    int ok = (value == 0xDEADBEEFu);

    printf("[E008] value=0x%08X %s\n", value, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
