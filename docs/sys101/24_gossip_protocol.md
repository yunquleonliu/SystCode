# Problem 24: Gossip Protocol (Simple)

## Description
Simulate a gossip protocol to propagate state across a cluster.

## Learning Objectives
- Randomization
- Convergence
- Epidemic algorithms

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
Loop:
         peer = select_random_peer()
         send(peer, my_state_digest)
         
     OnReceive(digest):
         diff = compare(digest, my_state)
         if diff:
             exchange_updates(diff)
```

## Solution Summary
The gossip protocol simulation has each node periodically select random peers and exchange state digests, comparing and synchronizing differences. This epidemic-style dissemination ensures eventual consistency and convergence across the cluster through randomized communication, achieving robustness against network partitions and node failures.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/24_gossip_protocol/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Information spread speed**
- **Convergence check (all nodes agree)**
- **Network partition simulation**
