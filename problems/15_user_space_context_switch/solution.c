#include <stdio.h>
#include <stdlib.h>

// On Linux, ucontext is standard. 
#ifdef __linux__
#include <ucontext.h>

static ucontext_t uctx_main, uctx_func1, uctx_func2;
static char stack1[16384];
static char stack2[16384];

void func2(void) {
    printf("  [Func2] Started\n");
    printf("  [Func2] Swapping back to Func1\n");
    swapcontext(&uctx_func2, &uctx_func1);
    printf("  [Func2] Resumed\n");
}

void func1(void) {
    printf("  [Func1] Started\n");
    printf("  [Func1] Swapping to Func2\n");
    swapcontext(&uctx_func1, &uctx_func2);
    printf("  [Func1] Back from Func2\n");
}

void solution() {}

int main(int argc, char *argv[]) {
    printf("User Space Context Switch Test:\n");

    if (getcontext(&uctx_func1) == -1) {
        perror("getcontext");
        exit(EXIT_FAILURE);
    }
    uctx_func1.uc_stack.ss_sp = stack1;
    uctx_func1.uc_stack.ss_size = sizeof(stack1);
    uctx_func1.uc_link = &uctx_main;
    makecontext(&uctx_func1, func1, 0);

    if (getcontext(&uctx_func2) == -1) {
        perror("getcontext");
        exit(EXIT_FAILURE);
    }
    uctx_func2.uc_stack.ss_sp = stack2;
    uctx_func2.uc_stack.ss_size = sizeof(stack2);
    uctx_func2.uc_link = &uctx_func1;
    makecontext(&uctx_func2, func2, 0);

    printf("[Main] Swapping to Func1\n");
    swapcontext(&uctx_main, &uctx_func1);
    printf("[Main] Back from Func1\n");

    printf("Test Passed\n");
    return 0;
}
#else
void solution() {}
int main() {
    printf("Not Linux (ucontext not available in this env), skipping.\n");
    return 0;
}
#endif
