/**
 * Problem 60: Flash Translation Layer (FTL)
 * Logical-to-physical block mapping for flash storage.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCKS 256

typedef struct {
    int logical_block;
    int physical_block;
    int valid;
    int erase_count;
} BlockMapping;

typedef struct {
    BlockMapping* map;
    int block_count;
    int free_blocks;
} FTL;

FTL* ftl_init(int blocks) {
    FTL* ftl = malloc(sizeof(FTL));
    ftl->map = calloc(blocks, sizeof(BlockMapping));
    ftl->block_count = blocks;
    ftl->free_blocks = blocks;
    printf("FTL initialized (%d blocks)\n", blocks);
    return ftl;
}

int ftl_write(FTL* ftl, int logical, const uint8_t* data) {
    // Simple linear mapping
    if (ftl->free_blocks == 0) {
        printf("FTL: No free blocks!\n");
        return -1;
    }
    
    int physical = ftl->block_count - ftl->free_blocks;
    ftl->map[logical].logical_block = logical;
    ftl->map[logical].physical_block = physical;
    ftl->map[logical].valid = 1;
    ftl->free_blocks--;
    
    printf("Write LBA %d -> PBA %d\n", logical, physical);
    return physical;
}

int ftl_read(FTL* ftl, int logical) {
    if (!ftl->map[logical].valid) return -1;
    printf("Read LBA %d -> PBA %d\n", logical, ftl->map[logical].physical_block);
    return ftl->map[logical].physical_block;
}

int main() {
    printf("=== Flash Translation Layer ===\n\n");
    FTL* ftl = ftl_init(256);
    ftl_write(ftl, 0, (uint8_t*)"data");
    ftl_write(ftl, 1, (uint8_t*)"more");
    ftl_read(ftl, 0);
    printf("Free blocks: %d\n", ftl->free_blocks);
    free(ftl->map);
    free(ftl);
    return 0;
}