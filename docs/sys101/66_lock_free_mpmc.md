# Problem 66: Lock-Free Ring (MPMC)

## Description
Multi-Producer Multi-Consumer queue using sequence counters.

## Learning Objectives
- **Concepts**: Memory Barriers, Atomic CAS, Head/Tail sequencing

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
// Pseudocode sketch for Lock-Free Ring (MPMC)
state = init_lock_free_ring_mpmc()
for event in input_stream:
    state = validate_and_apply(state, event)
    emit_if_needed(state)
return finalize(state)
```


## Why This Problem Matters
- **Lock-Free Ring (MPMC)** appears in real systems as a building block for reliability, performance, or scalability.
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
The lock-free Multi-Producer Multi-Consumer (MPMC) queue uses atomic operations and sequence numbers to enable concurrent enqueue/dequeue from multiple threads without locks. It employs techniques like CAS loops, memory ordering constraints, and bounded arrays with wrap-around indexing to achieve thread-safe, wait-free progress.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/66_lock_free_mpmc/solution.c)**
