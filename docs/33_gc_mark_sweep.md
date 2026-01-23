# Problem 33: Mark & Sweep GC

## Description
Implement a conservative Garbage Collector for C scanning the stack.

## Learning Objectives
- **Concepts**: Stack scanning, Reachability Graph, Memory Reclamation

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
The mark-and-sweep garbage collector scans the program stack and registers for potential pointers (conservative GC), marks all reachable heap objects by traversing pointer chains, then sweeps through the heap to free unmarked objects. This automatic memory management tracks object reachability graphs to reclaim unreferenced memory.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/33_gc_mark_sweep/solution.c)**
