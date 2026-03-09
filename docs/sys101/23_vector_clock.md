# Problem 23: Vector Clock

## Description
Implement vector clocks to track causal order in a system of N processes.

## Learning Objectives
- Partial ordering
- Logical clocks
- Distributed time

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
Event(pid):
         clock[pid]++
         
     Send(pid, msg):
         clock[pid]++
         msg.timestamp = clock
         
     Receive(pid, msg):
         clock[pid]++
         for i in 0..N:
             clock[i] = max(clock[i], msg.timestamp[i])
```


## Why This Problem Matters
- **Vector Clock** appears in real systems as a building block for reliability, performance, or scalability.
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
The vector clock implementation maintains an array of logical timestamps (one per process) that increments on local events and merges element-wise max on message receipt. This enables detection of concurrent events and determination of causal ordering (happens-before relationships) in distributed systems without requiring synchronized physical clocks.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/23_vector_clock/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Concurrent events detection**
- **Happens-before relation check**
- **Clock merging logic**
