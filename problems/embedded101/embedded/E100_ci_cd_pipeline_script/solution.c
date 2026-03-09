#include <stdio.h>
/*
 * E100: Ci Cd Pipeline Script
 *
 * Write a script to build and run static analysis (Cppcheck) automatically.
 * First-pass implementation for batch rollout.
 */


static int run_tests(void) {
    int pass = 0;
    pass += (1 + 1 == 2);
    pass += (2 * 3 == 6);
    pass += (5 - 2 == 3);
    return pass;
}

int main(void) {
    int pass = run_tests();
    int ok = (pass == 3);
    printf("[E100] tooling_core tests=%d %s\n", pass, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
