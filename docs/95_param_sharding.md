# Problem 95: Parameter Sharding

## Description
Simulate splitting weights across 2 devices (Tensor Parallelism).

## Learning Objectives
- **Concepts**: Distributed Matrix Mul, Communication Overhead, Synchronization

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
The parameter sharding implementation distributes large model weights across multiple devices/nodes to train models exceeding single-device memory. It partitions tensors, implements all-gather and reduce-scatter collectives, handles gradient synchronization, supports Zero Redundancy Optimizer (ZeRO) stages, and enables training of billion-parameter models.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/95_param_sharding/solution.c)**
