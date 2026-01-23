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

## Solution Summary
The mini debugger uses `ptrace` to attach to and control a target process, enabling inspection and modification of its execution state. It forks a child process with PTRACE_TRACEME, waits for it to stop, reads CPU registers using PTRACE_GETREGS, and can single-step through instructions, providing fundamental debugging capabilities.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/30_mini_debugger/solution.c)**

## Testing Standards
- **Launch target process**
- **Read Instruction Pointer (RIP/EIP)**
- **Single step execution**
