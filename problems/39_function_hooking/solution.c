/**
 * Problem 39: Function Hooking
 * Intercepting function calls at runtime.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#endif

// Original function to hook
int target_function(int x) {
    return x * 2;
}

// Hook function
int hook_function(int x) {
    printf("[HOOK] Intercepted call with x=%d\n", x);
    return x * 3;  // Different behavior
}

// Trampoline structure
typedef struct {
    void* original_func;
    void* hook_func;
    uint8_t original_bytes[16];
    int patch_size;
} Hook;

#if defined(__x86_64__) || defined(_M_X64)
// x64 JMP hook: mov rax, addr; jmp rax (12 bytes)
void install_hook_x64(Hook* h) {
    uint8_t* target = (uint8_t*)h->original_func;
    
    // Save original bytes
    memcpy(h->original_bytes, target, 12);
    h->patch_size = 12;
    
    // Make memory writable
#ifdef _WIN32
    DWORD old_protect;
    VirtualProtect(target, 12, PAGE_EXECUTE_READWRITE, &old_protect);
#else
    size_t page_size = sysconf(_SC_PAGESIZE);
    void* page = (void*)((uintptr_t)target & ~(page_size - 1));
    mprotect(page, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
    
    // Write jump to hook
    target[0] = 0x48;  // REX.W
    target[1] = 0xB8;  // mov rax, imm64
    *(uint64_t*)(target + 2) = (uint64_t)h->hook_func;
    target[10] = 0xFF; // jmp rax
    target[11] = 0xE0;
    
    printf("Installed hook at %p -> %p\n", h->original_func, h->hook_func);
}

void remove_hook_x64(Hook* h) {
    memcpy(h->original_func, h->original_bytes, h->patch_size);
    printf("Removed hook at %p\n", h->original_func);
}
#endif

// Function pointer table hooking (safer)
typedef int (*IntFunc)(int);

typedef struct {
    IntFunc* slot;
    IntFunc original;
    IntFunc hook;
} VTableHook;

IntFunc func_table[10];

void vtable_hook_install(VTableHook* h) {
    h->original = *h->slot;
    *h->slot = h->hook;
    printf("VTable hook installed\n");
}

void vtable_hook_remove(VTableHook* h) {
    *h->slot = h->original;
    printf("VTable hook removed\n");
}

// Wrapper/Detour pattern
IntFunc original_ptr = NULL;

int wrapper_hook(int x) {
    printf("[WRAPPER] Before call, x=%d\n", x);
    int result = original_ptr(x);  // Call original
    printf("[WRAPPER] After call, result=%d\n", result);
    return result + 100;  // Modify result
}

int main() {
    printf("=== Function Hooking ===\n\n");
    
    // Test original function
    printf("Original function:\n");
    printf("  target_function(5) = %d\n\n", target_function(5));
    
    // VTable-style hook demo
    printf("VTable-style hooking:\n");
    func_table[0] = target_function;
    
    VTableHook vh = {&func_table[0], NULL, hook_function};
    vtable_hook_install(&vh);
    printf("  func_table[0](5) = %d\n", func_table[0](5));
    vtable_hook_remove(&vh);
    printf("  func_table[0](5) = %d (restored)\n\n", func_table[0](5));
    
    // Wrapper pattern
    printf("Wrapper pattern:\n");
    original_ptr = target_function;
    printf("  wrapper_hook(5) = %d\n", wrapper_hook(5));
    
    return 0;
}