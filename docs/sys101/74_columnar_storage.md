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
// Add high-level logic here
```

## Solution Summary
The columnar storage format stores table columns contiguously rather than rows, optimizing for analytical queries that access few columns. It compresses similar values more effectively, enables SIMD operations on column data, supports column pruning during scans, and improves cache utilization for aggregate queries typical in OLAP workloads.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/74_columnar_storage/solution.c)**
