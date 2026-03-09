# Problem 101: Build Your Own Shell

## Description
Combine Process APIs, Signals, and Parsing into a working shell.

## Learning Objectives
- **Concepts**: fork/exec, Pipes, Signal Handling, Job Control

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
The custom shell implementation combines process management (`fork`/`exec`), input parsing, pipe handling, signal management (Ctrl-C, Ctrl-Z), and job control. It reads commands in a REPL, parses into tokens, executes built-in commands or launches processes, handles I/O redirection and pipelines, manages background jobs, and provides a fully functional command-line interface.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/101_capstone_shell/solution.c)**
