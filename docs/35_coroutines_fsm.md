# Problem 35: Coroutines (State Machine)

## Description
Implement stackless coroutines using Duff's Device / Macros.

## Learning Objectives
- **Concepts**: State Machines, Macro Expansion, Reentrancy

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
The stackless coroutine implementation uses Duff's Device and macros to transform coroutine code into a state machine. Each yield point is assigned a state label, and the coroutine function saves its state and returns; on re-entry, it jumps to the saved state using a switch statement, enabling cooperative multitasking without separate stacks.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/35_coroutines_fsm/solution.c)**
