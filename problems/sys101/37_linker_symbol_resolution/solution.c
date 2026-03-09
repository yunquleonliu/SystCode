/**
 * Problem 37: Linker Symbol Resolution
 * Resolving symbols across object files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    SYM_UNDEFINED,   // Referenced but not defined
    SYM_DEFINED,     // Strong definition
    SYM_COMMON,      // Tentative (uninitialized global)
    SYM_WEAK         // Weak symbol
} SymbolStrength;

typedef struct {
    char name[64];
    SymbolStrength strength;
    uint64_t value;
    const char* source;  // Which object file
} Symbol;

#define MAX_SYMBOLS 100

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

void symtab_init(SymbolTable* st) {
    st->count = 0;
}

Symbol* symtab_find(SymbolTable* st, const char* name) {
    for (int i = 0; i < st->count; i++) {
        if (strcmp(st->symbols[i].name, name) == 0) {
            return &st->symbols[i];
        }
    }
    return NULL;
}

bool symtab_add(SymbolTable* st, const char* name, SymbolStrength strength, 
                uint64_t value, const char* source) {
    Symbol* existing = symtab_find(st, name);
    
    if (existing) {
        // Resolution rules
        if (existing->strength == SYM_DEFINED && strength == SYM_DEFINED) {
            printf("ERROR: Multiple definition of '%s'\n", name);
            printf("  First: %s, Second: %s\n", existing->source, source);
            return false;
        }
        
        if (strength == SYM_DEFINED) {
            // Strong beats weak/common/undefined
            existing->strength = strength;
            existing->value = value;
            existing->source = source;
            printf("Resolved '%s' -> %s (strong)\n", name, source);
        } else if (existing->strength == SYM_UNDEFINED && strength != SYM_UNDEFINED) {
            existing->strength = strength;
            existing->value = value;
            existing->source = source;
            printf("Resolved '%s' -> %s\n", name, source);
        }
        // Otherwise keep existing
    } else {
        // New symbol
        Symbol* sym = &st->symbols[st->count++];
        strncpy(sym->name, name, 63);
        sym->strength = strength;
        sym->value = value;
        sym->source = source;
    }
    return true;
}

void symtab_print(SymbolTable* st) {
    printf("\nSymbol Table:\n");
    printf("%-20s %-12s %-12s %s\n", "Name", "Strength", "Value", "Source");
    printf("%-20s %-12s %-12s %s\n", "----", "--------", "-----", "------");
    
    for (int i = 0; i < st->count; i++) {
        Symbol* s = &st->symbols[i];
        const char* strength_str[] = {"UNDEFINED", "DEFINED", "COMMON", "WEAK"};
        printf("%-20s %-12s 0x%08lx   %s\n", 
               s->name, strength_str[s->strength], 
               (unsigned long)s->value, s->source ? s->source : "?");
    }
}

bool symtab_check_undefined(SymbolTable* st) {
    bool ok = true;
    for (int i = 0; i < st->count; i++) {
        if (st->symbols[i].strength == SYM_UNDEFINED) {
            printf("ERROR: Undefined reference to '%s'\n", st->symbols[i].name);
            ok = false;
        }
    }
    return ok;
}

int main() {
    printf("=== Linker Symbol Resolution ===\n\n");
    
    SymbolTable symtab;
    symtab_init(&symtab);
    
    // Simulate loading object files
    printf("Processing main.o:\n");
    symtab_add(&symtab, "main", SYM_DEFINED, 0x401000, "main.o");
    symtab_add(&symtab, "printf", SYM_UNDEFINED, 0, "main.o");
    symtab_add(&symtab, "helper", SYM_UNDEFINED, 0, "main.o");
    symtab_add(&symtab, "global_var", SYM_COMMON, 0, "main.o");
    
    printf("\nProcessing helper.o:\n");
    symtab_add(&symtab, "helper", SYM_DEFINED, 0x402000, "helper.o");
    symtab_add(&symtab, "global_var", SYM_DEFINED, 0x404000, "helper.o");
    symtab_add(&symtab, "weak_func", SYM_WEAK, 0x402100, "helper.o");
    
    printf("\nProcessing libc.so:\n");
    symtab_add(&symtab, "printf", SYM_DEFINED, 0x7f000000, "libc.so");
    symtab_add(&symtab, "weak_func", SYM_DEFINED, 0x7f001000, "libc.so");
    
    symtab_print(&symtab);
    
    printf("\nChecking for undefined symbols...\n");
    if (symtab_check_undefined(&symtab)) {
        printf("All symbols resolved successfully.\n");
    }
    
    return 0;
}