# Problem 9: Read-Write Lock (Write First)

## Description
Implement a RWLock that prioritizes writers to avoid write starvation.

## Learning Objectives
- Synchronization logic
- Reader/Writer states
- Condition variable precedence

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct RWLock {
         readers: int
         writers_waiting: int
         writer_active: bool
         cond_read, cond_write
     }
     
     write_lock():
         writers_waiting++
         while readers > 0 or writer_active:
             wait(cond_write)
         writers_waiting--
         writer_active = true
```

## Solution Summary
The writer-preferred read-write lock tracks the number of active readers, waiting writers, and whether a writer is active. Writers increment the waiting counter and block readers from entering, ensuring writers get priority. Multiple readers can acquire the lock concurrently when no writers are waiting or active, preventing writer starvation.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/09_read_write_lock/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Writers block readers**
- **Readers share access**
- **Writer priority test case**
