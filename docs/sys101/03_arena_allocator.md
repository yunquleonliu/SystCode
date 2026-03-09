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

## Solution Summary
The arena allocator uses a simple bump-pointer allocation strategy with a pre-allocated buffer and an offset tracker. Memory is allocated by incrementing the offset, providing O(1) allocation with excellent cache locality. The `arena_reset` function resets the offset to zero, enabling batch deallocation of all allocations at once without individual frees.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/03_arena_allocator/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Alloc sequence: A, B, C. Check offsets.**
- **Reset arena, alloc D. Check pointers reuse space.**
- **Overflow behavior**
