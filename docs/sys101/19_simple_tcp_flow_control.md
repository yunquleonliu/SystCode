# Problem 19: Simple TCP Flow Control

## Description
Simulate the TCP sliding window mechanism in userspace.

## Learning Objectives
- Networking algos
- Window management
- ACKs

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
send_packet(p):
         if in_flight < window_size:
             transmit(p)
             in_flight++
         else:
             buffer(p)
             
     receive_ack(ack_num):
         slide_window(ack_num)
         send_buffered()
```


## Why This Problem Matters
- **Simple TCP Flow Control** appears in real systems as a building block for reliability, performance, or scalability.
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
The TCP flow control simulation maintains a sliding window of in-flight packets and buffers excess packets when the window is full. Upon receiving ACKs, it advances the window base, decrements the in-flight count, and transmits buffered packets, implementing the core TCP congestion control mechanism that prevents sender from overwhelming the receiver.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/19_simple_tcp_flow_control/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Stop sending when window full**
- **Resume on ACK**
- **Retransmission simulation (optional)**
