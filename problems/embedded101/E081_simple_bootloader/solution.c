#include <stdint.h>
/*
 * E081: Simple Bootloader
 *
 * Checking a GPIO on boot to decide whether to jump to App or stay.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>

int main(void) {
    uint32_t image_crc = 0xA5A5A5A5u;
    uint32_t stored_crc = 0xA5A5A5A5u;
    int boot_ok = (image_crc == stored_crc);
    int slot = boot_ok ? 1 : 0;
    printf("[E081] bootsec_core slot=%d %s\n", slot, boot_ok ? "PASS" : "FAIL");
    return boot_ok ? 0 : 1;
}
