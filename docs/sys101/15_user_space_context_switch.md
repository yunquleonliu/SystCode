# Problem 15: User-space Context Switch

## Description
Implement a basic green-thread mechanism using `setjmp` and `longjmp`.

## Learning Objectives
- CPU Registers
- Stack switching
- Cooperative multitasking

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct Context {
         jmp_buf env
         stack_ptr
     }
     
     yield():
         if setjmp(current.env) == 0:
             next = scheduler()
             longjmp(next.env, 1)
```


## Why This Problem Matters
- **User-space Context Switch** appears in real systems as a building block for reliability, performance, or scalability.
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
The user-space context switch implementation uses `setjmp` to save the current execution context (registers and stack pointer) and `longjmp` to restore a previously saved context, enabling cooperative multitasking. Each green thread maintains its own stack and jump buffer, allowing the scheduler to switch between tasks without kernel involvement.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/15_user_space_context_switch/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Switch between two tasks**
- **Preserve local variables across switch**
- **Stack integrity**
