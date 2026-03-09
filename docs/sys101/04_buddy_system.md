# Problem 4: Buddy System

## Description
Implement a simplified Buddy System allocator for managing generic memory blocks.

## Learning Objectives
- Binary trees
- Power-of-2 splitting
- Coalescing free blocks

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
alloc(size):
         k = ceil(log2(size))
         if free_list[k] is not empty:
             return pop(free_list[k])
         else:
             block = alloc(size * 2) (recursive)
             split block into two buddies
             add one to free_list[k]
             return other
```


## Why This Problem Matters
- **Buddy System** appears in real systems as a building block for reliability, performance, or scalability.
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
The buddy system allocator manages memory by recursively splitting blocks into power-of-2 sized "buddies" and maintaining free lists for each size class. When allocating, it finds the smallest suitable block or splits larger blocks; when freeing, it coalesces adjacent buddy blocks back together using XOR address calculations to find buddy pairs, reducing fragmentation.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/04_buddy_system/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Alloc various power-of-2 sizes**
- **Alloc non-power-of-2 (padding)**
- **Free and verifying coalescing (merging buddies)**
