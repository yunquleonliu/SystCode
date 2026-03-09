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


## Why This Problem Matters
- **Gossip Protocol (Simple)** appears in real systems as a building block for reliability, performance, or scalability.
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
The gossip protocol simulation has each node periodically select random peers and exchange state digests, comparing and synchronizing differences. This epidemic-style dissemination ensures eventual consistency and convergence across the cluster through randomized communication, achieving robustness against network partitions and node failures.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/24_gossip_protocol/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Information spread speed**
- **Convergence check (all nodes agree)**
- **Network partition simulation**
