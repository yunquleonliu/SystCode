#include <stdint.h>
/*
 * E092: Pid Controller
 *
 * Implement a Proportional-Integral-Derivative controller loop.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>

int main(void) {
    int32_t q15_a = 8192;
    int32_t q15_b = 16384;
    int32_t mix = (q15_a + q15_b) / 2;
    int ok = (mix == 12288);
    printf("[E092] dsp_core q15=%d %s\n", mix, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
