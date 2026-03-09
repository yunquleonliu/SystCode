# Problem 16: Epoll Echo Server

## Description
Build a high-concurrency echo server using Linux `epoll`.

## Learning Objectives
- Event loops
- Non-blocking I/O
- Edge triggering

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
epoll_fd = epoll_create()
     epoll_ctl(add, listen_socket)
     
     loop:
         count = epoll_wait(events)
         for e in events:
             if e.fd == listen_socket:
                 accept()
             else:
                 recv(e.fd)
                 send(e.fd)
```


## Why This Problem Matters
- **Epoll Echo Server** appears in real systems as a building block for reliability, performance, or scalability.
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
The epoll-based echo server creates an event loop using `epoll_wait` to monitor multiple socket file descriptors simultaneously. It handles new connections on the listen socket, reads incoming data from client sockets, and echoes it back, all using non-blocking I/O with edge-triggered notifications for high concurrency and scalability.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/16_epoll_echo_server/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Handle multiple concurrent connections**
- **Echo correctness**
- **Client disconnect handling**
