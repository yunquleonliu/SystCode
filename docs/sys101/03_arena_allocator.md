# Problem 3: Arena Allocator

## Description
Create a Region-based memory management system (Arena) that frees specific blocks all at once.

## Learning Objectives
- Bump pointer allocation
- Cache locality
- Batch deallocation

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct Arena {
         buffer: byte array
         offset: size_t
     }
     
     function arena_alloc(arena, size):
         if arena.offset + size > arena.capacity:
             return NULL (or grow)
         ptr = arena.buffer + arena.offset
         arena.offset += size
         return ptr
     
     function arena_reset(arena):
         arena.offset = 0
```


## Why This Problem Matters
- **Arena Allocator** appears in real systems as a building block for reliability, performance, or scalability.
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
The arena allocator uses a simple bump-pointer allocation strategy with a pre-allocated buffer and an offset tracker. Memory is allocated by incrementing the offset, providing O(1) allocation with excellent cache locality. The `arena_reset` function resets the offset to zero, enabling batch deallocation of all allocations at once without individual frees.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/03_arena_allocator/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Alloc sequence: A, B, C. Check offsets.**
- **Reset arena, alloc D. Check pointers reuse space.**
- **Overflow behavior**
