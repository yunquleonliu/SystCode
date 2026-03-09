# Problem 87: Merkle Tree

## Description
Verify data integrity of large datasets (like Git/Blockchain).

## Learning Objectives
- **Concepts**: Cryptographic Hashing, Tree traversal, Difference detection

## Implementation Guide
1. **Understand Layout**: Review how this component works in a real system.
2. **Define Structures**: Create the `struct` needed.
3. **Core Logic**: Implement the algorithm.
4. **Edge Cases**: Handle memory boundaries, overflows, or concurrency.

## Testing Strategy
- Verify fundamental correctness.
- Test boundary conditions.
- (If applicable) Performance benchmark.

## Pseudocode Hint
```text
// Add high-level logic here
```

## Solution Summary
The Merkle tree constructs a binary hash tree where leaf nodes contain data hashes and internal nodes contain combined hashes of children. It enables efficient data verification, detects inconsistencies through root hash comparison, supports range proofs with O(log n) proof size, and is used in blockchain, distributed databases, and file synchronization.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/87_merkle_tree/solution.c)**
