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

## Solution Summary
The mini container uses Linux `clone` system call with namespace flags (CLONE_NEWUTS, CLONE_NEWPID, CLONE_NEWNS) to create an isolated process environment. The child process sets a new hostname, mounts filesystems, and executes a shell, achieving process, network, and filesystem isolation similar to Docker containers.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/29_mini_container/solution.c)**

## Testing Standards
- **Hostname inside != Hostname outside**
- **ps shows PID 1 inside**
- **File system isolation**
