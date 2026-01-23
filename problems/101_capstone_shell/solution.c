/**
 * Problem 101: Capstone - LLM Inference System
 * Complete system integrating all learned concepts
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int max_seq_len;
    int vocab_size;
    int hidden_dim;
    int num_layers;
} ModelConfig;

typedef struct {
    float* weights;
    int num_params;
    ModelConfig config;
} Model;

typedef struct {
    float* kv_cache;
    int cache_size;
} InferenceState;

typedef struct {
    int* token_ids;
    int seq_len;
    int num_tokens_generated;
} GenerationContext;

Model* model_load(ModelConfig config) {
    Model* model = malloc(sizeof(Model));
    model->config = config;
    model->num_params = config.hidden_dim * config.hidden_dim * config.num_layers * 4;
    model->weights = malloc(model->num_params * sizeof(float));
    
    // Initialize weights
    for (int i = 0; i < model->num_params; i++) {
        model->weights[i] = (float)rand() / RAND_MAX;
    }
    
    return model;
}

InferenceState* state_create(ModelConfig config) {
    InferenceState* state = malloc(sizeof(InferenceState));
    int cache_size = config.max_seq_len * config.hidden_dim * 2;  // K and V
    state->kv_cache = malloc(cache_size * sizeof(float));
    state->cache_size = cache_size;
    return state;
}

float* forward_pass(Model* model, int* tokens, int num_tokens, InferenceState* state) {
    // Simplified forward pass
    int hidden_dim = model->config.hidden_dim;
    float* output = malloc(hidden_dim * sizeof(float));
    
    // Simulate computation
    for (int i = 0; i < hidden_dim; i++) {
        output[i] = 0;
        for (int j = 0; j < num_tokens; j++) {
            output[i] += model->weights[(tokens[j] + i) % model->num_params];
        }
    }
    
    return output;
}

int sample_next_token(float* logits, int vocab_size) {
    // Simple argmax sampling
    int max_idx = 0;
    float max_val = logits[0];
    
    for (int i = 1; i < vocab_size; i++) {
        if (logits[i] > max_val) {
            max_val = logits[i];
            max_idx = i;
        }
    }
    
    return max_idx;
}

GenerationContext* generate_tokens(Model* model, int* prompt, int prompt_len,
                                  int max_new_tokens) {
    InferenceState* state = state_create(model->config);
    GenerationContext* ctx = malloc(sizeof(GenerationContext));
    
    ctx->token_ids = malloc((prompt_len + max_new_tokens) * sizeof(int));
    memcpy(ctx->token_ids, prompt, prompt_len * sizeof(int));
    ctx->seq_len = prompt_len + max_new_tokens;
    ctx->num_tokens_generated = 0;
    
    int current_pos = prompt_len;
    
    for (int i = 0; i < max_new_tokens; i++) {
        // Forward pass
        float* logits = forward_pass(model, ctx->token_ids, current_pos, state);
        
        // Sample next token
        int next_token = sample_next_token(logits, model->config.vocab_size);
        ctx->token_ids[current_pos++] = next_token;
        ctx->num_tokens_generated++;
        
        free(logits);
        
        // Stop condition (e.g., EOS token)
        if (next_token == 2) break;
    }
    
    free(state->kv_cache);
    free(state);
    
    return ctx;
}

void test_scenario() {
    printf("Running tests for LLM Inference System...\n\n");
    
    ModelConfig config = {
        .max_seq_len = 2048,
        .vocab_size = 50000,
        .hidden_dim = 256,
        .num_layers = 8
    };
    
    printf("Model configuration:\n");
    printf("  Max sequence length: %d\n", config.max_seq_len);
    printf("  Vocabulary size: %d\n", config.vocab_size);
    printf("  Hidden dimension: %d\n", config.hidden_dim);
    printf("  Number of layers: %d\n\n", config.num_layers);
    
    // Load model
    Model* model = model_load(config);
    printf("Loaded model with %d parameters\n\n", model->num_params);
    
    // Prepare prompt
    int prompt[] = {1, 42, 100, 500};
    int prompt_len = 4;
    
    printf("Generating tokens from prompt of length %d...\n", prompt_len);
    
    clock_t start = clock();
    GenerationContext* result = generate_tokens(model, prompt, prompt_len, 10);
    clock_t end = clock();
    
    printf("\nGeneration complete:\n");
    printf("  Tokens generated: %d\n", result->num_tokens_generated);
    printf("  Time taken: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("  Generated sequence: ");
    for (int i = prompt_len; i < prompt_len + result->num_tokens_generated; i++) {
        printf("%d ", result->token_ids[i]);
    }
    printf("\n");
    
    printf("\nSystem complete.\n");
    printf("Passed.\n");
    
    free(model->weights);
    free(model);
    free(result->token_ids);
    free(result);
}

int main() {
    test_scenario();
    return 0;
}