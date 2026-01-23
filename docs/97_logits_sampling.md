# Problem 97: Logits Sampling

## Description
Implement Top-K / Top-P (Nucleus) sampling algorithms.

## Learning Objectives
- **Concepts**: Probability distributions, Sorting, Cumulative Sum

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
The logits sampling implementation generates tokens from LLM outputs using strategies like top-k, top-p (nucleus), and temperature scaling. It filters probability distributions, applies softmax with temperature, performs weighted random sampling, handles special tokens, and balances creativity vs. coherence in text generation.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/LowLevelMaster/problems/97_logits_sampling/solution.c)**
