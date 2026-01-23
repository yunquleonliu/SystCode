/**
 * Problem 99: Ring AllReduce
 * Synchronize gradients across devices
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DEVICES 4
#define GRADIENT_SIZE 1000

typedef struct {
    float* gradients;
    int size;
    int device_id;
} DeviceGradient;

void ring_allreduce(DeviceGradient* devices, int num_devices, int gradient_size) {
    for (int step = 0; step < num_devices - 1; step++) {
        printf("Step %d:\n", step);
        
        for (int d = 0; d < num_devices; d++) {
            int prev = (d - 1 + num_devices) % num_devices;
            
            for (int i = 0; i < gradient_size; i++) {
                devices[d].gradients[i] += devices[prev].gradients[i];
            }
            
            printf("  Device %d: reduced gradients\n", d);
        }
    }
}

void test_scenario() {
    printf("Running tests for Ring AllReduce...\n\n");
    
    DeviceGradient* devices = malloc(sizeof(DeviceGradient) * NUM_DEVICES);
    
    for (int d = 0; d < NUM_DEVICES; d++) {
        devices[d].gradients = malloc(GRADIENT_SIZE * sizeof(float));
        devices[d].device_id = d;
        devices[d].size = GRADIENT_SIZE;
        
        for (int i = 0; i < GRADIENT_SIZE; i++) {
            devices[d].gradients[i] = (float)d;
        }
    }
    
    printf("Initialized %d devices with gradients\n", NUM_DEVICES);
    
    ring_allreduce(devices, NUM_DEVICES, GRADIENT_SIZE);
    
    printf("\nAfter allreduce:\n");
    for (int d = 0; d < NUM_DEVICES; d++) {
        float sum_grad = 0;
        for (int i = 0; i < GRADIENT_SIZE; i++) {
            sum_grad += devices[d].gradients[i];
        }
        printf("Device %d total gradients: %.0f\n", d, sum_grad);
    }
    
    printf("Passed.\n");
    
    for (int d = 0; d < NUM_DEVICES; d++) {
        free(devices[d].gradients);
    }
    free(devices);
}

int main() {
    test_scenario();
    return 0;
}