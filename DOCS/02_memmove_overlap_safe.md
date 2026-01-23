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

## Testing Standards
Your solution must pass the following test scenarios:
- **Overlap: dest starts inside src**
- **Overlap: src starts inside dest**
- **No overlap**
- **Size 0 copy**
