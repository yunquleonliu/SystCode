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

## Solution Summary
The user-space context switch implementation uses `setjmp` to save the current execution context (registers and stack pointer) and `longjmp` to restore a previously saved context, enabling cooperative multitasking. Each green thread maintains its own stack and jump buffer, allowing the scheduler to switch between tasks without kernel involvement.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/15_user_space_context_switch/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Switch between two tasks**
- **Preserve local variables across switch**
- **Stack integrity**
