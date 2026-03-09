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


## Why This Problem Matters
- **Memmove (Overlap-safe)** appears in real systems as a building block for reliability, performance, or scalability.
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
The implementation compares destination and source addresses to determine copy direction: forward copying when `dest < src` (low to high addresses), and backward copying when `dest > src` (high to low addresses) to prevent data corruption. The function handles edge cases like identical pointers and zero-length copies, with an optimized version using word-sized operations for performance.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/02_memmove_overlap_safe/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Overlap: dest starts inside src**
- **Overlap: src starts inside dest**
- **No overlap**
- **Size 0 copy**
