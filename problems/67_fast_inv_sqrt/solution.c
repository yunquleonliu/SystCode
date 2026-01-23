/**
 * Problem 67: Fast Inverse Square Root (Quake III)
 * Famous optimization for 1/sqrt(x) with Newton-Raphson
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

float fast_inv_sqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);  // Magic number!
    float y = *(float*)&i;
    
    // Newton-Raphson iteration (can repeat for better accuracy)
    y = y * (1.5f - xhalf * y * y);
    y = y * (1.5f - xhalf * y * y);
    
    return y;
}

float ref_inv_sqrt(float x) {
    return 1.0f / sqrtf(x);
}

void test_scenario() {
    printf("Running tests for Fast Inverse Square Root...\n\n");
    
    float test_vals[] = {1.0f, 4.0f, 9.0f, 16.0f, 100.0f};
    
    printf("Value\tFast\tRef\tError\n");
    printf("------\t------\t------\t------\n");
    
    for (int i = 0; i < 5; i++) {
        float x = test_vals[i];
        float fast = fast_inv_sqrt(x);
        float ref = ref_inv_sqrt(x);
        float error = fabsf(fast - ref) / ref * 100;
        
        printf("%.1f\t%.6f\t%.6f\t%.2f%%\n", x, fast, ref, error);
        assert(error < 1.0f);  // Less than 1% error
    }
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}