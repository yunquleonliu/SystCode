# Problem 78: Bitcask (Key-Value)

## Description
Implement a log-structured hash table (append-only file + in-mem map).

## Learning Objectives
- **Concepts**: Indexing, Sequential Writes, Compaction

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
The Bitcask key-value store uses an append-only log for writes with an in-memory hash table (keydir) mapping keys to disk locations. It provides fast writes through sequential I/O, fast reads via single disk seek, implements compaction to reclaim space from obsolete entries, and offers simple crash recovery by rebuilding the keydir from the log.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/78_bitcask_kv/solution.c)**
