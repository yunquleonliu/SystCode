#include <stdint.h>
#include <stdio.h>

static uint32_t popcount_u32(uint32_t value) {
#if defined(__GNUC__) || defined(__clang__)
    return (uint32_t)__builtin_popcount(value);
#else
    uint32_t count = 0;
    while (value != 0u) {
        value &= (value - 1u);
        ++count;
    }
    return count;
#endif
}

static void cpu_relax_nop(void) {
#if defined(__GNUC__) || defined(__clang__)
    __asm__ volatile("nop");
#endif
}

int main(void) {
    uint32_t value = 0xF0F0A50Fu;
    uint32_t count = popcount_u32(value);
    cpu_relax_nop();
    int ok = (count == 16u);
    printf("[E005] popcount=%u %s\n", count, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
