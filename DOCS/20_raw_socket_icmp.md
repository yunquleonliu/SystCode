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

## Testing Standards
Your solution must pass the following test scenarios:
- **Valid ICMP checksum**
- **Reply reception**
- **Root privilege requirement note**
