# Problem 59: Rotary Encoder Decoder

## Description
Decode quadrature signals from a physical knob (state machine).

## Learning Objectives
- **Concepts**: Gray Code, State Transitions, Debouncing

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
The rotary encoder implementation reads quadrature signals (A and B phases) from a rotary encoder to detect rotation direction and speed. It uses state machine logic or interrupt-driven phase tracking, debounces signals, counts encoder ticks, and determines clockwise/counterclockwise rotation for user input applications.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/59_rotary_encoder/solution.c)**
