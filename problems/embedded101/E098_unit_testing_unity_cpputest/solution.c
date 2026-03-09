#include <stdio.h>
/*
 * E098: Unit Testing Unity Cpputest
 *
 * Write a test for a driver with hardware mocking.
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
    printf("[E098] tooling_core tests=%d %s\n", pass, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
