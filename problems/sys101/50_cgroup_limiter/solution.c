/**
 * Problem 50: Cgroup Resource Limiter
 * CPU and memory resource limits.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char name[64];
    int64_t cpu_limit;
    int64_t mem_limit;
    int64_t mem_used;
} Cgroup;

Cgroup* cgroup_create(const char* name) {
    Cgroup* cg = calloc(1, sizeof(Cgroup));
    strncpy(cg->name, name, 63);
    cg->cpu_limit = -1;
    cg->mem_limit = -1;
    printf("Created cgroup '%s'\n", name);
    return cg;
}

void cgroup_set_cpu_limit(Cgroup* cg, int64_t limit) {
    cg->cpu_limit = limit;
    printf("CPU limit: %lld%%\n", (long long)limit);
}

void cgroup_set_mem_limit(Cgroup* cg, int64_t limit) {
    cg->mem_limit = limit;
    printf("Memory limit: %lld MB\n", (long long)(limit / (1024*1024)));
}

bool cgroup_alloc(Cgroup* cg, int64_t size) {
    if (cg->mem_limit > 0 && cg->mem_used + size > cg->mem_limit) {
        printf("OOM in '%s'\n", cg->name);
        return false;
    }
    cg->mem_used += size;
    return true;
}

int main() {
    printf("=== Cgroup Limiter ===\n\n");
    Cgroup* web = cgroup_create("web");
    cgroup_set_cpu_limit(web, 50);
    cgroup_set_mem_limit(web, 512 * 1024 * 1024);
    cgroup_alloc(web, 256 * 1024 * 1024);
    printf("Used: %lld MB\n", (long long)(web->mem_used / (1024*1024)));
    free(web);
    return 0;
}