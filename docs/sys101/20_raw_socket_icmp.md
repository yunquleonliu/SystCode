# Problem 20: Raw Socket ICMP

## Description
Construct and send an ICMP Echo Request (Ping) raw packet.

## Learning Objectives
- Raw sockets
- Checksum calculation
- IP headers

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)
     
     struct icmphdr icmp
     icmp.type = ICMP_ECHO
     icmp.checksum = calculate_checksum(&icmp)
     
     sendto(sock, &icmp, ...)
     recvfrom(sock, ...)
```


## Why This Problem Matters
- **Raw Socket ICMP** appears in real systems as a building block for reliability, performance, or scalability.
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
The raw socket ICMP implementation creates a raw socket with `IPPROTO_ICMP`, constructs an ICMP Echo Request packet with proper header fields (type, code, identifier, sequence), calculates the checksum using one's complement arithmetic, and sends/receives packets directly at the network layer, bypassing transport protocols.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/20_raw_socket_icmp/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Valid ICMP checksum**
- **Reply reception**
- **Root privilege requirement note**
