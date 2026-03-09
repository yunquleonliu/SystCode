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

## Solution Summary
The spinlock uses an atomic flag and Compare-And-Swap operations to implement mutual exclusion in user space. The lock function busy-waits in a loop attempting to CAS the flag from 0 to 1, with optional CPU pause instructions to reduce contention. The unlock function performs an atomic store to reset the flag to 0.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/06_spinlock_cas/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Mutual exclusion: Two threads increment shared counter**
- **Performance under contention (basic)**
- **Correctness of unlock**
