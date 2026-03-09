#include <stdint.h>
#include <stdio.h>

typedef struct {
    const char* name;
    uint32_t origin;
    uint32_t length;
} Region;

typedef struct {
    const char* name;
    uint32_t size;
    uint32_t address;
} Section;

static int place_section(const Region* region, uint32_t* cursor, Section* section) {
    uint32_t end = region->origin + region->length;
    if (*cursor + section->size > end) {
        return 0;
    }
    section->address = *cursor;
    *cursor += section->size;
    return 1;
}

int main(void) {
    Region flash = {"FLASH", 0x08000000u, 256u * 1024u};
    Region ram = {"RAM", 0x20000000u, 64u * 1024u};

    Section text = {".text", 40u * 1024u, 0};
    Section rodata = {".rodata", 8u * 1024u, 0};
    Section data = {".data", 4u * 1024u, 0};
    Section bss = {".bss", 12u * 1024u, 0};

    uint32_t flash_cursor = flash.origin;
    uint32_t ram_cursor = ram.origin;

    int ok = 1;
    ok &= place_section(&flash, &flash_cursor, &text);
    ok &= place_section(&flash, &flash_cursor, &rodata);
    ok &= place_section(&ram, &ram_cursor, &data);
    ok &= place_section(&ram, &ram_cursor, &bss);

    printf("[E002] %s text=0x%08X data=0x%08X bss=0x%08X\n", ok ? "PASS" : "FAIL", text.address, data.address, bss.address);
    return ok ? 0 : 1;
}
