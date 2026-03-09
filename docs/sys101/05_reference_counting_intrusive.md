# Problem 5: Reference Counting (Intrusive)

## Description
Implement an intrusive smart pointer where the reference count is embedded in the object itself.

## Learning Objectives
- Struct embedding
- `offsetof`
- Atomic operations
- Object lifecycles

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct RefCounted {
         count: atomic_int
     }
     
     function retain(obj):
         atomic_inc(obj.count)
         
     function release(obj):
         if atomic_dec(obj.count) == 0:
             free(obj)
```

## Solution Summary
The intrusive reference counting implementation embeds an atomic counter directly within the managed object structure. The `retain` function atomically increments the count, while `release` atomically decrements and frees the object when the count reaches zero, ensuring thread-safe lifetime management without requiring external control blocks.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/05_reference_counting_intrusive/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Single thread retain/release cycles**
- **Mock free function called exactly once**
- **Ref count hits zero logic**
