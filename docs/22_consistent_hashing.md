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

## Solution Summary
The consistent hashing implementation maintains a sorted hash ring where each physical node is mapped to multiple virtual nodes using hash functions. Keys are mapped to nodes by hashing the key and finding the first node clockwise on the ring (binary search), ensuring minimal key redistribution when nodes are added or removed from the cluster.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/22_consistent_hashing/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Key distribution balance**
- **Node addition impact (minimal reshuffle)**
- **Node removal handling**
