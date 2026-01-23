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

## Testing Standards
Your solution must pass the following test scenarios:
- **Writers block readers**
- **Readers share access**
- **Writer priority test case**
