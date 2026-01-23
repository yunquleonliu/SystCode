/**
 * Problem 32: Dynamic Linker Simulation
 * Symbol resolution and relocation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SYMBOLS 100
#define MAX_RELOCATIONS 100

typedef struct {
    char name[64];
    uint64_t address;
    int defined;  // 1 if defined, 0 if undefined
} Symbol;

typedef enum {
    R_ABSOLUTE,   // Absolute address
    R_PC_RELATIVE // PC-relative
} RelocType;

typedef struct {
    uint64_t offset;     // Where to patch
    char symbol[64];     // Symbol to resolve
    RelocType type;
    int64_t addend;
} Relocation;

typedef struct {
    char name[64];
    uint8_t* code;
    size_t code_size;
    Symbol symbols[MAX_SYMBOLS];
    int num_symbols;
    Relocation relocs[MAX_RELOCATIONS];
    int num_relocs;
    uint64_t base_address;
} Object;

void object_init(Object* obj, const char* name) {
    memset(obj, 0, sizeof(Object));
    strncpy(obj->name, name, 63);
}

void object_add_symbol(Object* obj, const char* name, uint64_t addr, int defined) {
    Symbol* sym = &obj->symbols[obj->num_symbols++];
    strncpy(sym->name, name, 63);
    sym->address = addr;
    sym->defined = defined;
    printf("  Symbol: %s @ 0x%lx (%s)\n", name, (unsigned long)addr, 
           defined ? "defined" : "undefined");
}

void object_add_reloc(Object* obj, uint64_t offset, const char* symbol, RelocType type) {
    Relocation* rel = &obj->relocs[obj->num_relocs++];
    rel->offset = offset;
    strncpy(rel->symbol, symbol, 63);
    rel->type = type;
    rel->addend = 0;
    printf("  Relocation: offset 0x%lx needs %s\n", (unsigned long)offset, symbol);
}

Symbol* find_symbol(Object* objs[], int num_objs, const char* name) {
    for (int i = 0; i < num_objs; i++) {
        for (int j = 0; j < objs[i]->num_symbols; j++) {
            if (objs[i]->symbols[j].defined && 
                strcmp(objs[i]->symbols[j].name, name) == 0) {
                return &objs[i]->symbols[j];
            }
        }
    }
    return NULL;
}

void link_objects(Object* objs[], int num_objs) {
    printf("\n=== Linking Phase ===\n");
    
    // Assign base addresses
    uint64_t addr = 0x400000;
    for (int i = 0; i < num_objs; i++) {
        objs[i]->base_address = addr;
        printf("Object %s loaded at 0x%lx\n", objs[i]->name, (unsigned long)addr);
        addr += 0x1000;  // 4KB per object
    }
    
    // Resolve relocations
    printf("\nResolving relocations:\n");
    for (int i = 0; i < num_objs; i++) {
        for (int j = 0; j < objs[i]->num_relocs; j++) {
            Relocation* rel = &objs[i]->relocs[j];
            Symbol* sym = find_symbol(objs, num_objs, rel->symbol);
            
            if (!sym) {
                printf("  ERROR: Undefined symbol %s\n", rel->symbol);
                continue;
            }
            
            uint64_t target = sym->address;
            uint64_t patch_addr = objs[i]->base_address + rel->offset;
            
            printf("  %s: patching 0x%lx with 0x%lx\n", 
                   rel->symbol, (unsigned long)patch_addr, (unsigned long)target);
        }
    }
}

int main() {
    printf("=== Dynamic Linker ===\n\n");
    
    Object main_obj, lib_obj;
    object_init(&main_obj, "main.o");
    object_init(&lib_obj, "libfoo.so");
    
    printf("Loading main.o:\n");
    object_add_symbol(&main_obj, "main", 0x0, 1);
    object_add_symbol(&main_obj, "printf", 0x0, 0);  // undefined
    object_add_reloc(&main_obj, 0x10, "printf", R_PC_RELATIVE);
    object_add_reloc(&main_obj, 0x20, "foo", R_PC_RELATIVE);
    
    printf("\nLoading libfoo.so:\n");
    object_add_symbol(&lib_obj, "foo", 0x100, 1);
    object_add_symbol(&lib_obj, "bar", 0x200, 1);
    object_add_symbol(&lib_obj, "printf", 0x0, 0);
    
    Object* objs[] = { &main_obj, &lib_obj };
    link_objects(objs, 2);
    
    return 0;
}