# Problem 29: Mini Container

## Description
Use Linux namespaces to isolate a process (hostname, PID, mount).

## Learning Objectives
- Namespaces (clone/unshare)
- chroot
- Isolation

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.

## Pseudocode Hint
```text
// Note: Linux specific
     flags = CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS
     pid = clone(child_func, stack, flags, arg)
     waitpid(pid)
     
     child_func():
         sethostname("container")
         exec("bin/sh")
```


## Why This Problem Matters
- **Mini Container** appears in real systems as a building block for reliability, performance, or scalability.
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
The mini container uses Linux `clone` system call with namespace flags (CLONE_NEWUTS, CLONE_NEWPID, CLONE_NEWNS) to create an isolated process environment. The child process sets a new hostname, mounts filesystems, and executes a shell, achieving process, network, and filesystem isolation similar to Docker containers.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/29_mini_container/solution.c)**

## Testing Standards
- **Hostname inside != Hostname outside**
- **ps shows PID 1 inside**
- **File system isolation**
