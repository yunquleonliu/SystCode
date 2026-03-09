/**
 * Problem 31: JIT Compiler
 * Runtime code generation and execution.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

typedef struct {
    uint8_t* code;
    size_t size;
    size_t capacity;
} JITBuffer;

JITBuffer* jit_create(size_t capacity) {
    JITBuffer* jit = malloc(sizeof(JITBuffer));
    
#ifdef _WIN32
    jit->code = VirtualAlloc(NULL, capacity, MEM_COMMIT | MEM_RESERVE, 
                             PAGE_EXECUTE_READWRITE);
#else
    jit->code = mmap(NULL, capacity, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
    
    jit->size = 0;
    jit->capacity = capacity;
    return jit;
}

void jit_emit(JITBuffer* jit, uint8_t byte) {
    if (jit->size < jit->capacity) {
        jit->code[jit->size++] = byte;
    }
}

void jit_emit_bytes(JITBuffer* jit, const uint8_t* bytes, size_t len) {
    for (size_t i = 0; i < len; i++) {
        jit_emit(jit, bytes[i]);
    }
}

// Generate: int add(int a, int b) { return a + b; }
void jit_compile_add(JITBuffer* jit) {
    // x86-64 System V ABI: args in RDI, RSI
    // mov eax, edi    ; 89 f8
    // add eax, esi    ; 01 f0  
    // ret             ; c3
    
    uint8_t code[] = {
        0x89, 0xf8,  // mov eax, edi
        0x01, 0xf0,  // add eax, esi
        0xc3         // ret
    };
    jit_emit_bytes(jit, code, sizeof(code));
    printf("Compiled add function (%zu bytes)\n", jit->size);
}

// Generate: int mul(int a, int b) { return a * b; }
void jit_compile_mul(JITBuffer* jit) {
    // imul eax, edi, 0  ; then add esi...
    // Actually simpler:
    // mov eax, edi
    // imul eax, esi
    // ret
    
    uint8_t code[] = {
        0x89, 0xf8,        // mov eax, edi
        0x0f, 0xaf, 0xc6,  // imul eax, esi
        0xc3               // ret
    };
    jit_emit_bytes(jit, code, sizeof(code));
    printf("Compiled mul function (%zu bytes)\n", jit->size);
}

typedef int (*IntBinaryFunc)(int, int);

void jit_destroy(JITBuffer* jit) {
#ifdef _WIN32
    VirtualFree(jit->code, 0, MEM_RELEASE);
#else
    munmap(jit->code, jit->capacity);
#endif
    free(jit);
}

int main() {
    printf("=== JIT Compiler ===\n\n");
    
    JITBuffer* jit = jit_create(4096);
    
    // Compile and run add
    size_t add_offset = jit->size;
    jit_compile_add(jit);
    
    IntBinaryFunc add_func = (IntBinaryFunc)(jit->code + add_offset);
    int result = add_func(10, 25);
    printf("add(10, 25) = %d\n", result);
    
    // Compile and run mul
    size_t mul_offset = jit->size;
    jit_compile_mul(jit);
    
    IntBinaryFunc mul_func = (IntBinaryFunc)(jit->code + mul_offset);
    result = mul_func(7, 8);
    printf("mul(7, 8) = %d\n", result);
    
    jit_destroy(jit);
    return 0;
}