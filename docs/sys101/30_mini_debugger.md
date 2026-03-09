# Problem 30: Mini Debugger

## Description
Implement a tracer using `ptrace` to stop a child process and inspect registers.

## Learning Objectives
- ptrace
- System Calls
- Register Inspection

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.

## Pseudocode Hint
```text
pid = fork()
     if pid == 0:
         ptrace(TRACEME)
         exec(target)
     else:
         wait()
         ptrace(GETREGS, pid, &regs)
         print("RIP:", regs.rip)
         ptrace(CONT, pid)
```


## Why This Problem Matters
- **Mini Debugger** appears in real systems as a building block for reliability, performance, or scalability.
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
The mini debugger uses `ptrace` to attach to and control a target process, enabling inspection and modification of its execution state. It forks a child process with PTRACE_TRACEME, waits for it to stop, reads CPU registers using PTRACE_GETREGS, and can single-step through instructions, providing fundamental debugging capabilities.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/30_mini_debugger/solution.c)**

## Testing Standards
- **Launch target process**
- **Read Instruction Pointer (RIP/EIP)**
- **Single step execution**
