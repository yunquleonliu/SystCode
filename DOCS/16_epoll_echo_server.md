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

## Testing Standards
Your solution must pass the following test scenarios:
- **Handle multiple concurrent connections**
- **Echo correctness**
- **Client disconnect handling**
