# Problem 22: Consistent Hashing

## Description
Implement consistent hashing for mapping keys to nodes.

## Learning Objectives
- Hashing
- Ring topology
- Binary search

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
AddNode(node):
         for v in 0..virtual_nodes:
             hash = sha1(node + v)
             ring.insert(hash, node)
             
     GetNode(key):
         hash = sha1(key)
         node = ring.find_first_node_ge(hash)
         if not found: return ring.first()
         return node
```


## Why This Problem Matters
- **Consistent Hashing** appears in real systems as a building block for reliability, performance, or scalability.
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
The consistent hashing implementation maintains a sorted hash ring where each physical node is mapped to multiple virtual nodes using hash functions. Keys are mapped to nodes by hashing the key and finding the first node clockwise on the ring (binary search), ensuring minimal key redistribution when nodes are added or removed from the cluster.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/22_consistent_hashing/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Key distribution balance**
- **Node addition impact (minimal reshuffle)**
- **Node removal handling**
