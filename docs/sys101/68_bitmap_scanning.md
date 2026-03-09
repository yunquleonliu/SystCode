# Problem 68: Bitmap Scanning (ffs)

## Description
Optimize finding the first set bit in large arrays (SWAR/SIMD).

## Learning Objectives
- **Concepts**: Bit Manipulation, CTZ/CLZ instructions, Word-level parallelism

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
The bitmap scanning implementation efficiently finds set or clear bits using CPU instructions like `__builtin_ctz` (count trailing zeros) or POPCNT. It represents sets compactly as bit arrays, performs fast membership tests, finds first/next set bit for iteration, and implements allocation bitmaps for memory managers or schedulers.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/68_bitmap_scanning/solution.c)**
