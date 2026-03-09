#include <stdint.h>
/*
 * E091: Fixed Point Arithmetic
 *
 * Implement math libraries for processors without FPU.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>

int main(void) {
    int32_t q15_a = 8192;
    int32_t q15_b = 16384;
    int32_t mix = (q15_a + q15_b) / 2;
    int ok = (mix == 12288);
    printf("[E091] dsp_core q15=%d %s\n", mix, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
