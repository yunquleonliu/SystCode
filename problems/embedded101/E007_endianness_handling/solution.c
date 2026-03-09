#include <stdint.h>
#include <stdio.h>

static int is_little_endian(void) {
    const uint16_t value = 0x0001u;
    return *((const uint8_t*)&value) == 0x01u;
}

static uint16_t bswap16(uint16_t value) {
    return (uint16_t)((value >> 8) | (value << 8));
}

static uint32_t bswap32(uint32_t value) {
    return ((value & 0x000000FFu) << 24) |
           ((value & 0x0000FF00u) << 8) |
           ((value & 0x00FF0000u) >> 8) |
           ((value & 0xFF000000u) >> 24);
}

int main(void) {
    uint16_t v16 = 0x1234u;
    uint32_t v32 = 0x89ABCDEFu;
    uint16_t s16 = bswap16(v16);
    uint32_t s32 = bswap32(v32);

    int ok = (s16 == 0x3412u) && (s32 == 0xEFCDAB89u);
    printf("[E007] endian=%s swap=%s\n", is_little_endian() ? "little" : "big", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
