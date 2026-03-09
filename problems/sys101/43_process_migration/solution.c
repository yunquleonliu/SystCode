/**
 * Problem 43: Process Migration
 * Checkpoint and restore process state.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t rip, rsp;
} RegisterState;

typedef struct {
    int pid;
    RegisterState regs;
    void* memory;
    size_t mem_size;
} ProcessCheckpoint;

ProcessCheckpoint* checkpoint_create(int pid) {
    ProcessCheckpoint* cp = calloc(1, sizeof(ProcessCheckpoint));
    cp->pid = pid;
    cp->regs.rip = 0x400000;
    cp->regs.rsp = 0x7fffffffe000;
    return cp;
}

void checkpoint_save(ProcessCheckpoint* cp, const char* filename) {
    FILE* f = fopen(filename, "wb");
    fwrite(&cp->pid, sizeof(cp->pid), 1, f);
    fwrite(&cp->regs, sizeof(cp->regs), 1, f);
    fclose(f);
    printf("Saved checkpoint to %s\n", filename);
}

ProcessCheckpoint* checkpoint_load(const char* filename) {
    FILE* f = fopen(filename, "rb");
    ProcessCheckpoint* cp = calloc(1, sizeof(ProcessCheckpoint));
    fread(&cp->pid, sizeof(cp->pid), 1, f);
    fread(&cp->regs, sizeof(cp->regs), 1, f);
    fclose(f);
    printf("Loaded checkpoint from %s\n", filename);
    return cp;
}

int main() {
    printf("=== Process Migration ===\n\n");
    ProcessCheckpoint* cp = checkpoint_create(12345);
    checkpoint_save(cp, "checkpoint.dat");
    free(cp);
    ProcessCheckpoint* restored = checkpoint_load("checkpoint.dat");
    printf("Restored PID: %d, RIP: 0x%llx\n", restored->pid, (unsigned long long)restored->regs.rip);
    free(restored);
    return 0;
}