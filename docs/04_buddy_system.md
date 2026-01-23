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

## Solution Summary
The buddy system allocator manages memory by recursively splitting blocks into power-of-2 sized "buddies" and maintaining free lists for each size class. When allocating, it finds the smallest suitable block or splits larger blocks; when freeing, it coalesces adjacent buddy blocks back together using XOR address calculations to find buddy pairs, reducing fragmentation.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/04_buddy_system/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Alloc various power-of-2 sizes**
- **Alloc non-power-of-2 (padding)**
- **Free and verifying coalescing (merging buddies)**
