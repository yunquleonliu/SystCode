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

## Solution Summary
The TCP flow control simulation maintains a sliding window of in-flight packets and buffers excess packets when the window is full. Upon receiving ACKs, it advances the window base, decrements the in-flight count, and transmits buffered packets, implementing the core TCP congestion control mechanism that prevents sender from overwhelming the receiver.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/19_simple_tcp_flow_control/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Stop sending when window full**
- **Resume on ACK**
- **Retransmission simulation (optional)**
