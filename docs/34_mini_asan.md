# Problem 34: Address Sanitizer (Mini-ASan)

## Description
Implement shadow memory logic to detect out-of-bounds access.

## Learning Objectives
- **Concepts**: Shadow Memory mapping, Poison values, Instrumentation

## Implementation Guide
1. **Understand Layout**: Review how this component works in a real system.
2. **Define Structures**: Create the `struct` needed.
3. **Core Logic**: Implement the algorithm.
4. **Edge Cases**: Handle memory boundaries, overflows, or concurrency.

## Testing Strategy
- Verify fundamental correctness.
- Test boundary conditions.
- (If applicable) Performance benchmark.

## Pseudocode Hint
```text
// Add high-level logic here
```

## Solution Summary
The mini AddressSanitizer creates red zones (inaccessible memory regions) around heap allocations to detect buffer overflows and use-after-free bugs. By intercepting malloc/free and poisoning surrounding bytes, it catches out-of-bounds accesses at runtime through instrumentation, providing memory safety debugging similar to ASan.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/34_mini_asan/solution.c)**
