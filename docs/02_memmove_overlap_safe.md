# Problem 2: Memmove (Overlap-safe)

## Description
Implement a distinct `memmove` function that handles overlapping memory regions correctly.

## Learning Objectives
- Pointer comparison
- Backwards copying
- Defensive coding

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
function my_memmove(dest, src, n):
         if dest < src:
             copy forward (0 to n)
         else if dest > src:
             copy backward (n-1 to 0)
         else:
             do nothing
```

## Solution Summary
The implementation compares destination and source addresses to determine copy direction: forward copying when `dest < src` (low to high addresses), and backward copying when `dest > src` (high to low addresses) to prevent data corruption. The function handles edge cases like identical pointers and zero-length copies, with an optimized version using word-sized operations for performance.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/02_memmove_overlap_safe/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Overlap: dest starts inside src**
- **Overlap: src starts inside dest**
- **No overlap**
- **Size 0 copy**
