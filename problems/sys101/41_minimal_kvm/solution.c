/**
 * Problem 41: Minimal KVM Virtualization
 * Simulate KVM virtual machine creation and execution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define GUEST_MEM_SIZE (64 * 1024)

typedef struct {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip, rflags;
} VMRegs;

typedef struct {
    int vm_id;
    uint8_t* guest_memory;
    VMRegs regs;
    bool running;
} VM;

VM* vm_create(int id) {
    VM* vm = calloc(1, sizeof(VM));
    vm->vm_id = id;
    vm->guest_memory = calloc(1, GUEST_MEM_SIZE);
    vm->regs.rip = 0x1000;
    vm->regs.rsp = 0x8000;
    vm->running = false;
    printf("VM %d created (64 KB)\n", id);
    return vm;
}

void vm_load_code(VM* vm, const uint8_t* code, size_t len, uint64_t addr) {
    if (addr + len > GUEST_MEM_SIZE) return;
    memcpy(vm->guest_memory + addr, code, len);
    printf("Loaded %zu bytes @ 0x%llx\n", len, (unsigned long long)addr);
}

int vm_run(VM* vm) {
    vm->running = true;
    printf("VM %d: Executing from RIP=0x%llx\n", vm->vm_id, (unsigned long long)vm->regs.rip);
    
    for (int i = 0; i < 10; i++) {
        uint8_t opcode = vm->guest_memory[vm->regs.rip];
        if (opcode == 0xF4) { // HLT
            vm->running = false;
            printf("  HLT @ 0x%llx\n", (unsigned long long)vm->regs.rip);
            return 0;
        } else if (opcode == 0x90) { // NOP
            vm->regs.rip++;
        } else {
            vm->regs.rip++;
        }
    }
    return 0;
}

void vm_destroy(VM* vm) {
    free(vm->guest_memory);
    free(vm);
    printf("VM destroyed\n");
}

int main() {
    printf("=== Minimal KVM ===\n\n");
    VM* vm = vm_create(1);
    uint8_t code[] = {0x90, 0x90, 0xF4};
    vm_load_code(vm, code, sizeof(code), 0x1000);
    vm_run(vm);
    vm_destroy(vm);
    return 0;
}