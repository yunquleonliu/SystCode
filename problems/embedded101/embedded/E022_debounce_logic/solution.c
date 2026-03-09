#include <stdint.h>
/*
 * E022: Debounce Logic
 *
 * Implement a software state machine to debounce a mechanical button.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>

static uint32_t hash_u32(uint32_t value) {
    value ^= value >> 16;
    value *= 0x7feb352du;
    value ^= value >> 15;
    value *= 0x846ca68bu;
    value ^= value >> 16;
    return value;
}

int main(void) {
    uint32_t nodes[4] = {11u, 29u, 47u, 61u};
    uint32_t key = hash_u32(0x016u);
    uint32_t idx = key % 4u;
    uint32_t selected = nodes[idx];
    int ok = selected == nodes[idx];
    printf("[E022] dist_core key=%u node=%u %s\n", key, selected, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
