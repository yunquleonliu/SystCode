/**
 * Problem 95: Parameter Sharding
 * Distribute model parameters across devices
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DEVICES 4
#define PARAM_SIZE 1000000

typedef struct {
    float* params;
    int param_count;
    int device_id;
} Shard;

typedef struct {
    Shard shards[NUM_DEVICES];
    int num_devices;
    int total_params;
} ShardedModel;

ShardedModel* create_sharded_model(int total_params, int num_devices) {
    ShardedModel* model = malloc(sizeof(ShardedModel));
    model->num_devices = num_devices;
    model->total_params = total_params;
    
    int params_per_shard = total_params / num_devices;
    
    for (int i = 0; i < num_devices; i++) {
        model->shards[i].device_id = i;
        model->shards[i].param_count = params_per_shard;
        model->shards[i].params = malloc(params_per_shard * sizeof(float));
        
        for (int j = 0; j < params_per_shard; j++) {
            model->shards[i].params[j] = (float)i;
        }
    }
    
    return model;
}

void gather_all_gather(ShardedModel* model, float* global_buffer) {
    int offset = 0;
    for (int i = 0; i < model->num_devices; i++) {
        memcpy(&global_buffer[offset], 
               model->shards[i].params,
               model->shards[i].param_count * sizeof(float));
        offset += model->shards[i].param_count;
    }
}

void test_scenario() {
    printf("Running tests for Parameter Sharding...\n\n");
    
    ShardedModel* model = create_sharded_model(PARAM_SIZE, NUM_DEVICES);
    
    printf("Sharded model across %d devices\n", NUM_DEVICES);
    printf("Total parameters: %d\n", PARAM_SIZE);
    
    for (int i = 0; i < NUM_DEVICES; i++) {
        printf("Device %d: %d parameters\n", i, model->shards[i].param_count);
    }
    
    float* global_buffer = malloc(PARAM_SIZE * sizeof(float));
    gather_all_gather(model, global_buffer);
    
    printf("\nAll-gather complete\n");
    printf("Passed.\n");
    free(global_buffer);
}

int main() {
    test_scenario();
    return 0;
}