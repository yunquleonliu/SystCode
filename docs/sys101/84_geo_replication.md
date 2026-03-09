# Problem 84: Geo-Replication Latency

## Description
Simulate consistency lag between regions (Quorum logic).

## Learning Objectives
- **Concepts**: Network partitions, CAP Theorem trade-offs, Latency

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
The geo-replication system synchronizes data across geographically distributed datacenters using asynchronous replication, conflict resolution strategies (last-write-wins, vector clocks), and multi-master or primary-backup topologies. It balances consistency, availability, and latency for global applications requiring disaster recovery and low-latency local reads.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/84_geo_replication/solution.c)**
