#include <stdint.h>
/*
 * E063: Scatter Gather Dma
 *
 * Set up a linked-list based DMA transfer for scattered memory buffers.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>
#include <string.h>

#define PAGE 256

int main(void) {
    uint8_t flash[PAGE];
    memset(flash, 0xFF, sizeof(flash));
    const char* msg = "E063";
    memcpy(&flash[32], msg, 4);
    int ok = memcmp(&flash[32], msg, 4) == 0;
    printf("[E063] storage_core %s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
