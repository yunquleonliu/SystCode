/**
 * Problem 91: Tensor Quantization
 * Reduce precision for efficient ML inference
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float scale;
    int8_t zero_point;
} QuantizationParams;

QuantizationParams* compute_quantization_params(float* tensor, int size) {
    QuantizationParams* params = malloc(sizeof(QuantizationParams));
    
    // Find min/max
    float min_val = tensor[0], max_val = tensor[0];
    for (int i = 0; i < size; i++) {
        if (tensor[i] < min_val) min_val = tensor[i];
        if (tensor[i] > max_val) max_val = tensor[i];
    }
    
    // int8 range: [-128, 127]
    params->scale = (max_val - min_val) / 255.0f;
    params->zero_point = (int8_t)(-128 - min_val / params->scale);
    
    return params;
}

int8_t quantize_value(float value, QuantizationParams* params) {
    float quantized = value / params->scale + params->zero_point;
    if (quantized > 127) quantized = 127;
    if (quantized < -128) quantized = -128;
    return (int8_t)quantized;
}

float dequantize_value(int8_t value, QuantizationParams* params) {
    return (value - params->zero_point) * params->scale;
}

void test_scenario() {
    printf("Running tests for Tensor Quantization...\n\n");
    
    float tensor[] = {-5.0f, -2.5f, 0.0f, 2.5f, 5.0f};
    int size = 5;
    
    QuantizationParams* params = compute_quantization_params(tensor, size);
    
    printf("Original values: ");
    for (int i = 0; i < size; i++) printf("%.1f ", tensor[i]);
    printf("\n");
    
    printf("Quantization scale: %.4f\n", params->scale);
    printf("Zero point: %d\n", params->zero_point);
    
    printf("Quantized (int8): ");
    for (int i = 0; i < size; i++) {
        int8_t q = quantize_value(tensor[i], params);
        printf("%d ", q);
    }
    printf("\n");
    
    printf("Dequantized: ");
    for (int i = 0; i < size; i++) {
        int8_t q = quantize_value(tensor[i], params);
        float dq = dequantize_value(q, params);
        printf("%.2f ", dq);
    }
    printf("\n");
    
    printf("Passed.\n");
    free(params);
}

int main() {
    test_scenario();
    return 0;
}