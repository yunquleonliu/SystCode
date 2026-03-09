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


## Why This Problem Matters
- **Reference Counting (Intrusive)** appears in real systems as a building block for reliability, performance, or scalability.
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
The intrusive reference counting implementation embeds an atomic counter directly within the managed object structure. The `retain` function atomically increments the count, while `release` atomically decrements and frees the object when the count reaches zero, ensuring thread-safe lifetime management without requiring external control blocks.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/05_reference_counting_intrusive/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Single thread retain/release cycles**
- **Mock free function called exactly once**
- **Ref count hits zero logic**
