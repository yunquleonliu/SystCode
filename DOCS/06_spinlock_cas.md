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

## Testing Standards
Your solution must pass the following test scenarios:
- **Mutual exclusion: Two threads increment shared counter**
- **Performance under contention (basic)**
- **Correctness of unlock**
