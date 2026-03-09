/**
 * Problem 30: Mini Debugger
 * Basic debugger using ptrace (Linux) or simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef __linux__
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#endif

typedef struct {
    uint64_t address;
    uint8_t original_byte;
    bool enabled;
} Breakpoint;

typedef struct {
    int pid;
    Breakpoint breakpoints[16];
    int bp_count;
    bool running;
} Debugger;

void debugger_init(Debugger* dbg) {
    memset(dbg, 0, sizeof(Debugger));
    dbg->pid = -1;
}

#ifdef __linux__
void debugger_attach(Debugger* dbg, int pid) {
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) < 0) {
        perror("ptrace attach");
        return;
    }
    waitpid(pid, NULL, 0);
    dbg->pid = pid;
    dbg->running = true;
    printf("Attached to process %d\n", pid);
}

void debugger_set_breakpoint(Debugger* dbg, uint64_t addr) {
    if (dbg->bp_count >= 16) return;
    
    // Read original byte
    long data = ptrace(PTRACE_PEEKTEXT, dbg->pid, (void*)addr, NULL);
    
    Breakpoint* bp = &dbg->breakpoints[dbg->bp_count++];
    bp->address = addr;
    bp->original_byte = (uint8_t)(data & 0xFF);
    bp->enabled = true;
    
    // Write INT3 (0xCC)
    long int3_data = (data & ~0xFF) | 0xCC;
    ptrace(PTRACE_POKETEXT, dbg->pid, (void*)addr, (void*)int3_data);
    
    printf("Breakpoint %d set at 0x%lx\n", dbg->bp_count, addr);
}

void debugger_continue(Debugger* dbg) {
    ptrace(PTRACE_CONT, dbg->pid, NULL, NULL);
    int status;
    waitpid(dbg->pid, &status, 0);
    
    if (WIFSTOPPED(status)) {
        printf("Process stopped (signal %d)\n", WSTOPSIG(status));
    }
}

void debugger_get_registers(Debugger* dbg) {
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, dbg->pid, NULL, &regs);
    printf("RIP: 0x%llx\n", regs.rip);
    printf("RSP: 0x%llx\n", regs.rsp);
    printf("RAX: 0x%llx\n", regs.rax);
}

void debugger_detach(Debugger* dbg) {
    ptrace(PTRACE_DETACH, dbg->pid, NULL, NULL);
    dbg->running = false;
    printf("Detached from process %d\n", dbg->pid);
}

#else
// Simulation for non-Linux systems
void debugger_attach(Debugger* dbg, int pid) {
    dbg->pid = pid;
    dbg->running = true;
    printf("[Sim] Attached to process %d\n", pid);
}

void debugger_set_breakpoint(Debugger* dbg, uint64_t addr) {
    if (dbg->bp_count >= 16) return;
    Breakpoint* bp = &dbg->breakpoints[dbg->bp_count++];
    bp->address = addr;
    bp->enabled = true;
    printf("[Sim] Breakpoint %d set at 0x%lx\n", dbg->bp_count, (unsigned long)addr);
}

void debugger_continue(Debugger* dbg) {
    printf("[Sim] Continuing execution...\n");
    printf("[Sim] Hit breakpoint at 0x%lx\n", 
           dbg->bp_count > 0 ? (unsigned long)dbg->breakpoints[0].address : 0UL);
}

void debugger_get_registers(Debugger* dbg) {
    (void)dbg;
    printf("[Sim] Registers:\n");
    printf("  RIP: 0x00000000004011a0\n");
    printf("  RSP: 0x00007fffffffdc00\n");
    printf("  RAX: 0x0000000000000000\n");
}

void debugger_detach(Debugger* dbg) {
    dbg->running = false;
    printf("[Sim] Detached from process %d\n", dbg->pid);
}
#endif

void debugger_interactive(Debugger* dbg) {
    char cmd[256];
    
    printf("\nMini Debugger Commands:\n");
    printf("  b <addr>  - Set breakpoint\n");
    printf("  c         - Continue\n");
    printf("  r         - Show registers\n");
    printf("  q         - Quit\n\n");
    
    while (dbg->running) {
        printf("(dbg) ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        
        if (cmd[0] == 'b') {
            uint64_t addr;
            if (sscanf(cmd + 1, "%lx", (unsigned long*)&addr) == 1) {
                debugger_set_breakpoint(dbg, addr);
            }
        } else if (cmd[0] == 'c') {
            debugger_continue(dbg);
        } else if (cmd[0] == 'r') {
            debugger_get_registers(dbg);
        } else if (cmd[0] == 'q') {
            debugger_detach(dbg);
            break;
        }
    }
}

int main() {
    printf("=== Mini Debugger ===\n\n");
    
    Debugger dbg;
    debugger_init(&dbg);
    
    // Demo: attach to fake PID
    debugger_attach(&dbg, 12345);
    debugger_set_breakpoint(&dbg, 0x401000);
    debugger_get_registers(&dbg);
    debugger_continue(&dbg);
    debugger_detach(&dbg);
    
    return 0;
}