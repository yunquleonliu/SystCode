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


## Why This Problem Matters
- **Barrier** appears in real systems as a building block for reliability, performance, or scalability.
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
The barrier synchronization primitive maintains a count of arrived threads and blocks until all N threads reach the barrier point. Using a mutex and condition variable, threads increment the count and wait; when the last thread arrives, it resets the count and broadcasts to wake all waiting threads, allowing them to proceed together.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/10_barrier/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Sync N threads**
- **Threads proceed only after all arrive**
- **Reuse barrier multiple times**
