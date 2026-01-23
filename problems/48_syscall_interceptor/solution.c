/**
 * Problem 48: Syscall Interceptor
 * Hook and monitor system calls.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long (*SyscallFn)(long, long, long);

typedef struct {
    const char* name;
    SyscallFn handler;
    int count;
} Syscall;

#define MAX_SYSCALLS 32
Syscall syscall_table[MAX_SYSCALLS];
int syscall_count = 0;

long sys_read(long fd, long buf, long count) {
    printf("[read] fd=%ld, count=%ld\n", fd, count);
    return count;
}

long sys_write(long fd, long buf, long count) {
    printf("[write] fd=%ld, count=%ld\n", fd, count);
    if (count > 1000) return -1;
    return count;
}

void syscall_register(const char* name, SyscallFn fn) {
    if (syscall_count < MAX_SYSCALLS) {
        syscall_table[syscall_count].name = name;
        syscall_table[syscall_count].handler = fn;
        syscall_table[syscall_count].count = 0;
        printf("Registered %s\n", name);
        syscall_count++;
    }
}

int main() {
    printf("=== Syscall Interceptor ===\n\n");
    syscall_register("read", sys_read);
    syscall_register("write", sys_write);
    
    syscall_table[0].handler(0, (long)"buf", 100);
    syscall_table[0].count++;
    syscall_table[1].handler(1, (long)"out", 50);
    syscall_table[1].count++;
    
    printf("\nStats: read=%d, write=%d\n", 
           syscall_table[0].count, syscall_table[1].count);
    return 0;
}