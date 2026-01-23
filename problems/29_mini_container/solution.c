/**
 * Problem 29: Mini Container (Linux namespaces simulation)
 * Process isolation using namespaces concept.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __linux__
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#endif

typedef struct {
    bool pid_ns;
    bool net_ns;
    bool mnt_ns;
    bool uts_ns;
    char hostname[64];
    char rootfs[256];
} ContainerConfig;

typedef struct {
    int pid;
    ContainerConfig config;
    bool running;
} Container;

void container_init_config(ContainerConfig* cfg) {
    cfg->pid_ns = true;
    cfg->net_ns = true;
    cfg->mnt_ns = true;
    cfg->uts_ns = true;
    strcpy(cfg->hostname, "container");
    strcpy(cfg->rootfs, "/");
}

#ifdef __linux__
static int container_main(void* arg) {
    ContainerConfig* cfg = (ContainerConfig*)arg;
    
    // Set hostname in UTS namespace
    if (cfg->uts_ns) {
        sethostname(cfg->hostname, strlen(cfg->hostname));
    }
    
    printf("[Container] PID inside: %d\n", getpid());
    printf("[Container] Hostname: %s\n", cfg->hostname);
    
    // Would normally exec shell or application here
    printf("[Container] Running isolated process...\n");
    sleep(1);
    
    return 0;
}
#endif

int container_run(Container* c) {
#ifdef __linux__
    int flags = SIGCHLD;
    if (c->config.pid_ns) flags |= CLONE_NEWPID;
    if (c->config.net_ns) flags |= CLONE_NEWNET;
    if (c->config.mnt_ns) flags |= CLONE_NEWNS;
    if (c->config.uts_ns) flags |= CLONE_NEWUTS;
    
    char* stack = malloc(1024 * 1024);
    if (!stack) return -1;
    
    printf("[Host] Creating container with namespaces:\n");
    printf("  PID: %s, NET: %s, MNT: %s, UTS: %s\n",
           c->config.pid_ns ? "yes" : "no",
           c->config.net_ns ? "yes" : "no",
           c->config.mnt_ns ? "yes" : "no",
           c->config.uts_ns ? "yes" : "no");
    
    c->pid = clone(container_main, stack + 1024*1024, flags, &c->config);
    if (c->pid < 0) {
        free(stack);
        return -1;
    }
    
    c->running = true;
    printf("[Host] Container PID (from host): %d\n", c->pid);
    
    waitpid(c->pid, NULL, 0);
    c->running = false;
    free(stack);
    
    printf("[Host] Container exited\n");
    return 0;
#else
    printf("[Simulation] Container would run with:\n");
    printf("  Hostname: %s\n", c->config.hostname);
    printf("  PID namespace: %s\n", c->config.pid_ns ? "enabled" : "disabled");
    printf("  Network namespace: %s\n", c->config.net_ns ? "enabled" : "disabled");
    printf("  Mount namespace: %s\n", c->config.mnt_ns ? "enabled" : "disabled");
    printf("  (Linux required for actual isolation)\n");
    return 0;
#endif
}

int main() {
    printf("=== Mini Container ===\n\n");
    
    Container c;
    container_init_config(&c.config);
    strcpy(c.config.hostname, "mycontainer");
    c.running = false;
    
    container_run(&c);
    
    return 0;
}