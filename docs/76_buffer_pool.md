# Problem 76: Buffer Pool Manager

## Description
Manage a cache of disk pages in memory with eviction policies.

## Learning Objectives
- **Concepts**: Pinning/Unpinning, LRU/Clock Replacer, Dirty Flags

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
The buffer pool manages a cache of disk pages in memory with eviction policies (LRU/Clock) and dirty page tracking. It pins pages during use, writes dirty pages back on eviction, maintains a hash table for fast page lookup, and implements latching for concurrency control, serving as the memory manager for database storage engines.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/76_buffer_pool/solution.c)**
