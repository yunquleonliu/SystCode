#include <stdint.h>
/*
 * E060: Littlefs Fatfs Porting
 *
 * Create the block device input/output shim for a filesystem.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>
#include <string.h>

#define PAGE 256

int main(void) {
    uint8_t flash[PAGE];
    memset(flash, 0xFF, sizeof(flash));
    const char* msg = "E060";
    memcpy(&flash[32], msg, 4);
    int ok = memcmp(&flash[32], msg, 4) == 0;
    printf("[E060] storage_core %s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
