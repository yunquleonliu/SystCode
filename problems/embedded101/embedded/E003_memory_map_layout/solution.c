#include <stdint.h>
#include <stdio.h>

typedef struct {
    const char* name;
    uint32_t start;
    uint32_t size;
    uint32_t cursor;
} MemoryRegion;

static int overlap(const MemoryRegion* first, const MemoryRegion* second) {
    uint32_t first_end = first->start + first->size;
    uint32_t second_end = second->start + second->size;
    return !(first_end <= second->start || second_end <= first->start);
}

static int region_alloc(MemoryRegion* region, uint32_t bytes, uint32_t* out_addr) {
    if (region->cursor + bytes > region->start + region->size) {
        return 0;
    }
    *out_addr = region->cursor;
    region->cursor += bytes;
    return 1;
}

int main(void) {
    MemoryRegion stack = {"stack", 0x2001C000u, 0x2000u, 0x2001C000u};
    MemoryRegion heap = {"heap", 0x20010000u, 0xB000u, 0x20010000u};
    MemoryRegion shared = {"shared", 0x2000F000u, 0x1000u, 0x2000F000u};

    int layout_ok = !overlap(&stack, &heap) && !overlap(&stack, &shared) && !overlap(&heap, &shared);

    uint32_t alloc1 = 0;
    uint32_t alloc2 = 0;
    int alloc_ok = region_alloc(&heap, 0x400, &alloc1) && region_alloc(&heap, 0x800, &alloc2);

    printf("[E003] layout=%s alloc=%s first=0x%08X second=0x%08X\n",
           layout_ok ? "PASS" : "FAIL",
           alloc_ok ? "PASS" : "FAIL",
           alloc1,
           alloc2);
    return (layout_ok && alloc_ok) ? 0 : 1;
}
