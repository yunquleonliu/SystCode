# Problem 39: Function Hooking (Trampoline)

## Description
Overwrite function prologue to redirect execution to a hook.

## Learning Objectives
- **Concepts**: Code Patching, Relative Jumps, Instruction preservation

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
The function hooking implementation patches the prologue of target functions with jump instructions to redirect execution to hook handlers. It saves original bytes, changes memory protection to writable, injects a trampoline that jumps to the hook function, and optionally chains to the original, enabling runtime interception for profiling, debugging, or instrumentation.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/39_function_hooking/solution.c)**
