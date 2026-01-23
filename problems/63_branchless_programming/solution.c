/**
 * Problem 63: Branchless Programming
 * Implement common operations without conditional branches
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Branchless absolute value
int abs_branchless(int x) {
    int mask = x >> 31;
    return (x + mask) ^ mask;
}

// Branchless minimum
int min_branchless(int a, int b) {
    return b + ((a - b) & ((a - b) >> 31));
}

// Branchless maximum
int max_branchless(int a, int b) {
    return a - ((a - b) & ((a - b) >> 31));
}

// Branchless conditional assignment
int conditional_assign(int cond, int a, int b) {
    // if (cond) result = a; else result = b;
    int mask = -(int)(cond != 0);
    return (a & mask) | (b & ~mask);
}

// Branchless sign extraction
int sign_branchless(int x) {
    return (x > 0) - (x < 0);
}

void test_scenario() {
    printf("Running tests for Branchless Programming...\n\n");
    
    // Test abs
    assert(abs_branchless(-42) == 42);
    assert(abs_branchless(42) == 42);
    assert(abs_branchless(0) == 0);
    printf("abs: OK\n");
    
    // Test min
    assert(min_branchless(5, 3) == 3);
    assert(min_branchless(3, 5) == 3);
    printf("min: OK\n");
    
    // Test max
    assert(max_branchless(5, 3) == 5);
    assert(max_branchless(3, 5) == 5);
    printf("max: OK\n");
    
    // Test conditional
    assert(conditional_assign(1, 10, 20) == 10);
    assert(conditional_assign(0, 10, 20) == 20);
    printf("conditional: OK\n");
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}