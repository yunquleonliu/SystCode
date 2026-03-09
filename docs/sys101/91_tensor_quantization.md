# Problem 91: Tensor Quantization (Int8)

## Description
Implement quantization logic (Float32 -> Int8) for inference.

## Learning Objectives
- **Concepts**: Precision reduction, Scaling factors, Zero-points

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
The tensor quantization implementation converts floating-point weights/activations to lower precision (INT8, INT4) to reduce model size and inference latency. It computes scale factors and zero points, performs per-tensor or per-channel quantization, implements dequantization for computation, and handles quantization-aware training techniques for minimal accuracy loss.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/91_tensor_quantization/solution.c)**
