# Problem 77: External Merge Sort

## Description
Sort a file larger than available RAM using K-way merge.

## Learning Objectives
- **Concepts**: I/O minimization, Streaming, File Handles

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
The external merge sort handles datasets larger than memory by dividing data into sorted runs that fit in RAM, writing them to disk, then merging multiple runs using a priority queue (k-way merge). It minimizes I/O through optimal merge fan-out, demonstrates external algorithm techniques for big data processing when data cannot fit in memory.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/77_external_merge_sort/solution.c)**
