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

## Testing Standards
Your solution must pass the following test scenarios:
- **Concurrent events detection**
- **Happens-before relation check**
- **Clock merging logic**
