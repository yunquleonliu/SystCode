/**
 * Problem 49: Bootloader Logic
 * Stage1/Stage2 bootloader simulation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECTOR_SIZE 512
#define BOOT_SIG 0xAA55

void stage1_bootloader() {
    printf("Stage 1: Loading MBR\n");
    
    uint8_t mbr[SECTOR_SIZE];
    memset(mbr, 0, SECTOR_SIZE);
    mbr[510] = 0x55;
    mbr[511] = 0xAA;
    
    uint16_t sig = *(uint16_t*)(mbr + 510);
    if (sig == BOOT_SIG) {
        printf("  Valid boot signature\n");
        printf("  Loading Stage 2...\n");
    }
}

void stage2_bootloader() {
    printf("Stage 2: Setting up\n");
    printf("  Enabling A20 line\n");
    printf("  Loading kernel...\n");
    printf("  Entering protected mode\n");
    printf("  Jumping to kernel\n");
}

int main() {
    printf("=== Bootloader Logic ===\n\n");
    stage1_bootloader();
    printf("\n");
    stage2_bootloader();
    return 0;
}