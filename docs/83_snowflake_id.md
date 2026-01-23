# Problem 83: Distributed ID Generator

## Description
Implement Twitter Snowflake algorithm (Time + Machine + Seq).

## Learning Objectives
- **Concepts**: Bit packing, Clock synchronization, Unique IDs

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
The Snowflake ID generator creates globally unique, time-ordered 64-bit IDs by combining timestamp bits, datacenter/worker IDs, and sequence numbers. It generates IDs without coordination across machines, provides natural time-based sorting, handles clock skew, and supports high-throughput ID generation for distributed systems.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/83_snowflake_id/solution.c)**
