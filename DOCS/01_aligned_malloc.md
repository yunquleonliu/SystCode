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

## Testing Standards
Your solution must pass the following test scenarios:
- **Verify alignment of returned pointer (ptr % align == 0)**
- **Verify data writing doesn't crash**
- **Verify aligned_free works without leaks**
