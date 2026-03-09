# Problem 6: Spinlock (CAS)

## Description
Implement a user-space spinlock using atomic Compare-And-Swap (CAS) primitives.

## Learning Objectives
- Atomics (__atomic / stdatomic.h)
- Busy waiting
- CPU yielding

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct Spinlock { flag: int = 0 }
     
     function lock(s):
         while NOT CAS(&s.flag, 0, 1):
             pause() or yield()
             
     function unlock(s):
         atomic_store(&s.flag, 0)
```


## Why This Problem Matters
- **Spinlock (CAS)** appears in real systems as a building block for reliability, performance, or scalability.
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
The spinlock uses an atomic flag and Compare-And-Swap operations to implement mutual exclusion in user space. The lock function busy-waits in a loop attempting to CAS the flag from 0 to 1, with optional CPU pause instructions to reduce contention. The unlock function performs an atomic store to reset the flag to 0.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/06_spinlock_cas/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Mutual exclusion: Two threads increment shared counter**
- **Performance under contention (basic)**
- **Correctness of unlock**
