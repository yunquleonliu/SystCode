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
// Pseudocode sketch for Geo-Replication Latency
state = init_geo_replication_latency()
for event in input_stream:
    state = validate_and_apply(state, event)
    emit_if_needed(state)
return finalize(state)
```


## Why This Problem Matters
- **Geo-Replication Latency** appears in real systems as a building block for reliability, performance, or scalability.
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
The geo-replication system synchronizes data across geographically distributed datacenters using asynchronous replication, conflict resolution strategies (last-write-wins, vector clocks), and multi-master or primary-backup topologies. It balances consistency, availability, and latency for global applications requiring disaster recovery and low-latency local reads.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/84_geo_replication/solution.c)**
