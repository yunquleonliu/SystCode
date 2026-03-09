# Problem 37: Linker Symbol Resolution

## Description
Simulate how a linker resolves strong vs weak symbols across object files.

## Learning Objectives
- **Concepts**: Symbol Tables, Weak/Strong definitions, Common blocks

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
The linker symbol resolution simulates how the linker resolves undefined symbols across object files by maintaining global and local symbol tables. It processes each object file's symbols, resolves references, handles weak symbols, detects conflicts, and performs relocation to generate the final executable with correctly linked addresses.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/37_linker_symbol_resolution/solution.c)**
