# Problem 25: Raft Heartbeat

## Description
Simulate the Leader heartbeat and Follower timeout logic of Raft.

## Learning Objectives
- State management
- Timeouts
- Leader election

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
Leader:
         loop:
             sleep(heartbeat_interval)
             send(APPEND_ENTRIES) to all
             
     Follower:
         loop:
             wait_for_message(timeout)
             if timeout:
                 become_candidate()
             if receive(APPEND_ENTRIES):
                 reset_timer()
```


## Why This Problem Matters
- **Raft Heartbeat** appears in real systems as a building block for reliability, performance, or scalability.
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
The Raft heartbeat mechanism has the leader periodically send APPEND_ENTRIES messages to all followers at regular intervals. Followers reset their election timers upon receiving heartbeats; if a timeout occurs without hearing from the leader, the follower transitions to candidate state and initiates leader election, ensuring cluster availability.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/25_raft_heartbeat/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Leader maintains authority**
- **Follower timeout triggers election**
- **Heartbeat resets timers**
