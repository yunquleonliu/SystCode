# Problem 1: Aligned Malloc

## Description
Implement a memory allocator that supports custom alignment.

## Learning Objectives
- Bit manipulation
- Pointer arithmetic
- Memory layout

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
function aligned_malloc(size, alignment):
         total_size = size + alignment + sizeof(void*)
         raw_ptr = malloc(total_size)
         if raw_ptr is NULL: return NULL
         
         addr = (uintptr)raw_ptr + sizeof(void*)
         aligned_addr = (addr + alignment - 1) & ~(alignment - 1)
         
         ptr = (void*)aligned_addr
         (ptr - sizeof(void*)) = raw_ptr
         return ptr
```


## Why This Problem Matters
- **Aligned Malloc** appears in real systems as a building block for reliability, performance, or scalability.
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
The implementation allocates extra space to ensure proper alignment by over-allocating memory, computing an aligned address using bitwise operations `(addr + alignment - 1) & ~(alignment - 1)`, and storing the original pointer just before the aligned address for proper deallocation. The `aligned_free` function retrieves the stored original pointer and frees it.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/01_aligned_malloc/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Verify alignment of returned pointer (ptr % align == 0)**
- **Verify data writing doesn't crash**
- **Verify aligned_free works without leaks**
