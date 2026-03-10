# Problem 74: Columnar Storage (Parquet)

## Description
Simulate a column-oriented layout with Run-Length Encoding.

## Learning Objectives
- **Concepts**: Compression, CPU Vectorization friendliness, Access Patterns

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
// Pseudocode sketch for Columnar Storage (Parquet)
state = init_columnar_storage_parquet()
for event in input_stream:
    state = validate_and_apply(state, event)
    emit_if_needed(state)
return finalize(state)
```


## Why This Problem Matters
- **Columnar Storage (Parquet)** appears in real systems as a building block for reliability, performance, or scalability.
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
The columnar storage format stores table columns contiguously rather than rows, optimizing for analytical queries that access few columns. It compresses similar values more effectively, enables SIMD operations on column data, supports column pruning during scans, and improves cache utilization for aggregate queries typical in OLAP workloads.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/74_columnar_storage/solution.c)**
