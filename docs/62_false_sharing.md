# Problem 62: False Sharing Demo

## Description
Demonstrate performance drop when threads write to same cache line strings.

## Learning Objectives
- **Concepts**: L1 Cache Lines, Padding/Alignment, Multi-core scaling

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
The false sharing demonstration shows how concurrent threads accessing different variables on the same cache line cause cache coherence traffic and performance degradation. The solution pads data structures to ensure each thread's variables reside on separate cache lines (64-byte alignment), eliminating false sharing and improving parallel performance.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/62_false_sharing/solution.c)**
