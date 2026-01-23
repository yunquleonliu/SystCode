/**
 * Problem 100: Prompt Engine
 * Dynamic prompt construction for LLMs
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROMPT_LEN 8192
#define MAX_EXAMPLES 10

typedef struct {
    const char* input;
    const char* output;
} ExamplePair;

typedef struct {
    char instruction[1024];
    ExamplePair examples[MAX_EXAMPLES];
    int num_examples;
} PromptTemplate;

PromptTemplate* prompt_create(const char* instruction) {
    PromptTemplate* template = malloc(sizeof(PromptTemplate));
    strncpy(template->instruction, instruction, 1023);
    template->num_examples = 0;
    return template;
}

void prompt_add_example(PromptTemplate* template, const char* input, const char* output) {
    if (template->num_examples < MAX_EXAMPLES) {
        template->examples[template->num_examples].input = input;
        template->examples[template->num_examples].output = output;
        template->num_examples++;
    }
}

char* prompt_build(PromptTemplate* template) {
    char* prompt = malloc(MAX_PROMPT_LEN);
    int pos = 0;
    
    pos += snprintf(&prompt[pos], MAX_PROMPT_LEN - pos, 
                   "Instruction: %s\n\n", template->instruction);
    
    pos += snprintf(&prompt[pos], MAX_PROMPT_LEN - pos, "Examples:\n");
    for (int i = 0; i < template->num_examples; i++) {
        pos += snprintf(&prompt[pos], MAX_PROMPT_LEN - pos,
                       "Input: %s\nOutput: %s\n\n",
                       template->examples[i].input,
                       template->examples[i].output);
    }
    
    return prompt;
}

void test_scenario() {
    printf("Running tests for Prompt Engineering...\n\n");
    
    PromptTemplate* template = prompt_create("Translate English to French");
    
    prompt_add_example(template, "Hello", "Bonjour");
    prompt_add_example(template, "Thank you", "Merci");
    prompt_add_example(template, "Goodbye", "Au revoir");
    
    char* prompt = prompt_build(template);
    
    printf("Generated prompt:\n");
    printf("--\n%s--\n", prompt);
    
    printf("\nPrompt length: %lu characters\n", strlen(prompt));
    printf("Passed.\n");
    
    free(prompt);
    free(template);
}

int main() {
    test_scenario();
    return 0;
}