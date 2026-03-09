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

## Solution Summary
The round-robin scheduler maintains a runqueue of processes and allocates each process a fixed time quantum (slice). It dequeues a process, runs it for the quantum duration, and either completes it or re-enqueues it at the back of the queue, ensuring fair CPU allocation and preventing starvation through cyclic scheduling.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/26_round_robin_scheduler/solution.c)**

## Testing Standards
- **Fairness check (processes get equal turns)**
- **Completion of all processes**
- **Quantum value impact**
