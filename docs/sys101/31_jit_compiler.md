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


## Why This Problem Matters
- **JIT Compiler (x64)** appears in real systems as a building block for reliability, performance, or scalability.
- Mastering this problem improves your ability to reason about low-level tradeoffs under constraints.

## Step-by-Step Tutoring Guide
1. **Model first**: define invariants and expected state transitions before coding.
2. **Minimal baseline**: implement the simplest correct path.
3. **Harden edges**: handle boundary inputs, error propagation, and cleanup paths.
4. **Optimize last**: tune only after tests prove behavior.

## Common Pitfalls
- Treating happy-path correctness as enough.
- Missing ownership/lifetime rules for memory or resources.
- Ignoring concurrent access patterns and race windows.
- Over-optimizing without measurements.

## Debug & Validation Checklist
- Verify invariants after every major operation.
- Add targeted tests for boundary and stress cases.
- Inspect failure paths as carefully as success paths.
- Confirm complexity/latency assumptions with simple measurements.

## Further Practice
1. Implement a second variant with a different tradeoff (speed vs clarity).
2. Add instrumentation counters for visibility.
3. Document one production-style failure mode and mitigation.

## Solution Summary
The JIT compiler allocates executable memory using `mmap` with `PROT_READ | PROT_WRITE | PROT_EXEC` flags, writes raw x64 machine code (opcodes) directly into the allocated buffer following the x64 calling convention, then casts the buffer to a function pointer and invokes it. This enables runtime code generation and execution.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/31_jit_compiler/solution.c)**
