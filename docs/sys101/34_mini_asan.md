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


## Why This Problem Matters
- **Address Sanitizer (Mini-ASan)** appears in real systems as a building block for reliability, performance, or scalability.
- Mastering this problem improves your ability to reason about low-level tradeoffs under constraints.

## Step-by-Step Tutoring Guide
1. **Model first**: define invariants and expected state transitions before coding.
2. **Minimal baseline**: implement the simplest correct path.
3. **Harden edges**: handle boundary inputs, error propagation, and cleanup paths.
4. **Optimize last**: tune only after tests prove behavior.

## Common Pitfalls
- Treating happy-path correctness as enough.
- Missing ownership/lifetime rules for memory or resources.
- Ignoring concurrent access patterns and race windows.
- Over-optimizing without measurements.

## Debug & Validation Checklist
- Verify invariants after every major operation.
- Add targeted tests for boundary and stress cases.
- Inspect failure paths as carefully as success paths.
- Confirm complexity/latency assumptions with simple measurements.

## Further Practice
1. Implement a second variant with a different tradeoff (speed vs clarity).
2. Add instrumentation counters for visibility.
3. Document one production-style failure mode and mitigation.

## Solution Summary
The mini AddressSanitizer creates red zones (inaccessible memory regions) around heap allocations to detect buffer overflows and use-after-free bugs. By intercepting malloc/free and poisoning surrounding bytes, it catches out-of-bounds accesses at runtime through instrumentation, providing memory safety debugging similar to ASan.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/34_mini_asan/solution.c)**
