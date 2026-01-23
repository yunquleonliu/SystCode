# Problem 10: Barrier

## Description
Implement a synchronization barrier where threads wait until N threads reach the point.

## Learning Objectives
- Coordination
- Thread blocking
- Spurious wakeups

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
wait():
         lock(mutex)
         count++
         if count == target:
             count = 0
             broadcast(cond)
         else:
             while count < target: // careful with generations
                 wait(cond, mutex)
         unlock(mutex)
```

## Solution Summary
The barrier synchronization primitive maintains a count of arrived threads and blocks until all N threads reach the barrier point. Using a mutex and condition variable, threads increment the count and wait; when the last thread arrives, it resets the count and broadcasts to wake all waiting threads, allowing them to proceed together.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/10_barrier/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Sync N threads**
- **Threads proceed only after all arrive**
- **Reuse barrier multiple times**
