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

## Testing Standards
Your solution must pass the following test scenarios:
- **Leader maintains authority**
- **Follower timeout triggers election**
- **Heartbeat resets timers**
