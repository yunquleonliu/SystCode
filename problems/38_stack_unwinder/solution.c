/**
 * Problem 38: Stack Unwinder
 * Walking the call stack for debugging/profiling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef __GNUC__
#include <execinfo.h>
#endif

#define MAX_FRAMES 64

typedef struct {
    void* address;
    const char* function;
    const char* file;
    int line;
} StackFrame;

typedef struct {
    StackFrame frames[MAX_FRAMES];
    int depth;
} StackTrace;

// Manual frame pointer walking (x86-64)
void unwind_fp(void** buffer, int max_depth, int* depth) {
#if defined(__x86_64__) && defined(__GNUC__)
    void** fp;
    __asm__ volatile("mov %%rbp, %0" : "=r"(fp));
    
    *depth = 0;
    while (fp && *depth < max_depth) {
        void* ret_addr = fp[1];
        if (!ret_addr) break;
        
        buffer[(*depth)++] = ret_addr;
        fp = (void**)*fp;
    }
#else
    *depth = 0;
#endif
}

// Use libunwind/backtrace if available
int capture_stacktrace(void** buffer, int max_depth) {
#ifdef __GNUC__
    return backtrace(buffer, max_depth);
#else
    return 0;
#endif
}

void print_stacktrace() {
    void* buffer[MAX_FRAMES];
    
#ifdef __GNUC__
    int depth = backtrace(buffer, MAX_FRAMES);
    char** symbols = backtrace_symbols(buffer, depth);
    
    printf("Stack trace (%d frames):\n", depth);
    for (int i = 0; i < depth; i++) {
        printf("  #%d: %p %s\n", i, buffer[i], symbols ? symbols[i] : "??");
    }
    
    free(symbols);
#else
    printf("Stack trace (simulated):\n");
    printf("  #0: 0x00401234 in func_c\n");
    printf("  #1: 0x00401200 in func_b\n");
    printf("  #2: 0x004011a0 in func_a\n");
    printf("  #3: 0x00401100 in main\n");
#endif
}

// Simulated DWARF-style unwind info
typedef struct {
    uint64_t start_pc;
    uint64_t end_pc;
    int cfa_offset;   // Stack frame size
    int ra_offset;    // Return address offset from CFA
} UnwindEntry;

UnwindEntry unwind_table[] = {
    {0x401000, 0x401100, 16, -8},   // main
    {0x401100, 0x401200, 32, -8},   // func_a
    {0x401200, 0x401300, 48, -8},   // func_b
};

UnwindEntry* find_unwind_entry(uint64_t pc) {
    int n = sizeof(unwind_table) / sizeof(unwind_table[0]);
    for (int i = 0; i < n; i++) {
        if (pc >= unwind_table[i].start_pc && pc < unwind_table[i].end_pc) {
            return &unwind_table[i];
        }
    }
    return NULL;
}

// Test functions to create stack frames
void func_c() {
    printf("=== In func_c ===\n");
    print_stacktrace();
}

void func_b() {
    func_c();
}

void func_a() {
    func_b();
}

int main() {
    printf("=== Stack Unwinder ===\n\n");
    
    func_a();
    
    printf("\n--- Unwind Table ---\n");
    int n = sizeof(unwind_table) / sizeof(unwind_table[0]);
    for (int i = 0; i < n; i++) {
        UnwindEntry* e = &unwind_table[i];
        printf("PC 0x%lx-0x%lx: CFA=%d, RA=%d\n",
               (unsigned long)e->start_pc, (unsigned long)e->end_pc,
               e->cfa_offset, e->ra_offset);
    }
    
    return 0;
}