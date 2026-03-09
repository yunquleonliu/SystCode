# Problem 26: Round-Robin Scheduler

## Description
Implement a simulation of a Round-Robin process scheduler.

## Learning Objectives
- Runqueues
- Time Slices (Quantum)
- Context Switching

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.

## Pseudocode Hint
```text
struct Process { pid, state, remaining_time }
     queue runqueue
     
     schedule(quantum):
         while runqueue not empty:
             p = dequeue()
             run(p, quantum)
             if p.finished:
                 cleanup(p)
             else:
                 enqueue(p)
```


## Why This Problem Matters
- **Round-Robin Scheduler** appears in real systems as a building block for reliability, performance, or scalability.
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
The round-robin scheduler maintains a runqueue of processes and allocates each process a fixed time quantum (slice). It dequeues a process, runs it for the quantum duration, and either completes it or re-enqueues it at the back of the queue, ensuring fair CPU allocation and preventing starvation through cyclic scheduling.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/26_round_robin_scheduler/solution.c)**

## Testing Standards
- **Fairness check (processes get equal turns)**
- **Completion of all processes**
- **Quantum value impact**
