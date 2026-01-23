# Problem 31: JIT Compiler (x64)

## Description
Allocate RWX memory, write raw x64 opcodes, and execute function at runtime.

## Learning Objectives
- **Concepts**: mmap PROT_EXEC, ABI calling convention, Instruction Encoding

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
The JIT compiler allocates executable memory using `mmap` with `PROT_READ | PROT_WRITE | PROT_EXEC` flags, writes raw x64 machine code (opcodes) directly into the allocated buffer following the x64 calling convention, then casts the buffer to a function pointer and invokes it. This enables runtime code generation and execution.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/31_jit_compiler/solution.c)**
