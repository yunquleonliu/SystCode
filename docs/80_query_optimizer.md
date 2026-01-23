# Problem 80: Query Optimizer (Cost)

## Description
Simple cost estimation between Index Scan vs Seq Scan.

## Learning Objectives
- **Concepts**: Table Statistics, Selectivity Estimation, Plan Selection

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
The query optimizer transforms SQL queries into efficient execution plans by estimating costs of different join orders and access methods. It uses statistics (cardinality, selectivity), applies relational algebra transformations, considers index usage, and employs dynamic programming or greedy algorithms to find the lowest-cost plan, minimizing query execution time.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/80_query_optimizer/solution.c)**
