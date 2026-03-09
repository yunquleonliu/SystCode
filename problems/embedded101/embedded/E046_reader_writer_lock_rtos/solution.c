#include <stdio.h>
/*
 * E046: Reader Writer Lock Rtos
 *
 * Prioritize readers or writers in an embedded context.
 * First-pass implementation for batch rollout.
 */


static int rms_schedulable(const int* c, const int* t, int n) {
    double util = 0.0;
    for (int i = 0; i < n; ++i) util += (double)c[i] / (double)t[i];
    double bound = 0.779;
    return util <= bound;
}

int main(void) {
    int c[3] = {1, 1, 2};
    int t[3] = {4, 5, 10};
    int ok = rms_schedulable(c, t, 3);
    printf("[E046] realtime_core %s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
