/**
 * Problem 07: Lock-Free Stack (Treiber Stack)
 * Wait-free push, lock-free pop using CAS.
 * Addresses ABA problem with tagged pointers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <assert.h>

// Node for the stack
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Tagged pointer to handle ABA problem
// Uses lower bits for tag (assumes 8-byte alignment)
typedef struct {
    _Atomic(uintptr_t) head;  // Packed: pointer + tag
} LFStack;

#define PTR_MASK (~(uintptr_t)0xF)  // Assumes 16-byte alignment
#define TAG_MASK 0xF

static inline Node* get_ptr(uintptr_t tagged) {
    return (Node*)(tagged & PTR_MASK);
}

static inline unsigned get_tag(uintptr_t tagged) {
    return tagged & TAG_MASK;
}

static inline uintptr_t make_tagged(Node* ptr, unsigned tag) {
    return ((uintptr_t)ptr) | (tag & TAG_MASK);
}

void lfs_init(LFStack* stack) {
    atomic_init(&stack->head, 0);
}

void lfs_push(LFStack* stack, int value) {
    // Allocate with alignment for tagged pointer
    Node* node = (Node*)aligned_alloc(16, sizeof(Node));
    node->value = value;
    
    uintptr_t old_head, new_head;
    do {
        old_head = atomic_load(&stack->head);
        node->next = get_ptr(old_head);
        new_head = make_tagged(node, get_tag(old_head) + 1);
    } while (!atomic_compare_exchange_weak(&stack->head, &old_head, new_head));
}

bool lfs_pop(LFStack* stack, int* value) {
    uintptr_t old_head, new_head;
    Node* node;
    
    do {
        old_head = atomic_load(&stack->head);
        node = get_ptr(old_head);
        if (node == NULL) {
            return false;  // Stack empty
        }
        new_head = make_tagged(node->next, get_tag(old_head) + 1);
    } while (!atomic_compare_exchange_weak(&stack->head, &old_head, new_head));
    
    *value = node->value;
    // Note: In real code, use hazard pointers or epoch-based reclamation
    // free(node);  // Dangerous without proper memory reclamation
    return true;
}

bool lfs_is_empty(LFStack* stack) {
    return get_ptr(atomic_load(&stack->head)) == NULL;
}

// Simple version without ABA protection (for comparison)
typedef struct {
    _Atomic(Node*) head;
} SimpleLFStack;

void simple_init(SimpleLFStack* stack) {
    atomic_init(&stack->head, NULL);
}

void simple_push(SimpleLFStack* stack, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    
    Node* old_head;
    do {
        old_head = atomic_load(&stack->head);
        node->next = old_head;
    } while (!atomic_compare_exchange_weak(&stack->head, &old_head, node));
}

bool simple_pop(SimpleLFStack* stack, int* value) {
    Node* old_head;
    Node* new_head;
    
    do {
        old_head = atomic_load(&stack->head);
        if (old_head == NULL) return false;
        new_head = old_head->next;
    } while (!atomic_compare_exchange_weak(&stack->head, &old_head, new_head));
    
    *value = old_head->value;
    // free(old_head);  // Needs safe reclamation
    return true;
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

void test_simple_stack() {
    printf("Test: Simple lock-free stack... ");
    SimpleLFStack stack;
    simple_init(&stack);
    
    simple_push(&stack, 10);
    simple_push(&stack, 20);
    simple_push(&stack, 30);
    
    int val;
    assert(simple_pop(&stack, &val) && val == 30);
    assert(simple_pop(&stack, &val) && val == 20);
    assert(simple_pop(&stack, &val) && val == 10);
    assert(!simple_pop(&stack, &val));  // Empty
    
    printf("PASSED\n");
}

void test_tagged_stack() {
    printf("Test: Tagged pointer stack... ");
    LFStack stack;
    lfs_init(&stack);
    
    lfs_push(&stack, 100);
    lfs_push(&stack, 200);
    
    int val;
    assert(lfs_pop(&stack, &val) && val == 200);
    assert(lfs_pop(&stack, &val) && val == 100);
    assert(lfs_is_empty(&stack));
    
    printf("PASSED\n");
}

void test_lifo_order() {
    printf("Test: LIFO ordering... ");
    SimpleLFStack stack;
    simple_init(&stack);
    
    for (int i = 0; i < 100; i++) {
        simple_push(&stack, i);
    }
    
    for (int i = 99; i >= 0; i--) {
        int val;
        assert(simple_pop(&stack, &val));
        assert(val == i);
    }
    
    printf("PASSED\n");
}

void test_empty_pop() {
    printf("Test: Pop from empty stack... ");
    SimpleLFStack stack;
    simple_init(&stack);
    
    int val;
    assert(!simple_pop(&stack, &val));
    
    printf("PASSED\n");
}

int main() {
    printf("=== Lock-Free Stack Tests ===\n\n");
    test_simple_stack();
    test_tagged_stack();
    test_lifo_order();
    test_empty_pop();
    printf("\nAll tests passed!\n");
    return 0;
}
