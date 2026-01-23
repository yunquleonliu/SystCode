# Problem 50: Cgroup Resource Limiter

## Description
Simulate tracking CPU quotas and Memory pages for a process group.

## Learning Objectives
- **Concepts**: Accounting, Throttling, Resource Hierarchy

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
The cgroup resource limiter simulates tracking and enforcing CPU quotas and memory limits for process groups. It maintains accounting structures for resource usage, implements throttling when quotas are exceeded, and supports hierarchical resource limits, demonstrating how Linux cgroups provide resource isolation and management.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/50_cgroup_limiter/solution.c)**
