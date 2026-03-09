# E038: Memory Pool (Fixed Block)

## Objective
- Implementing a deterministic O(1) memory allocator for the OS.

## Background
- Module: RTOS Concepts & Kernel Design (20 Problems)
- Scope: Embedded systems docs-first specification before implementation.

## Requirements
- Define a clear API contract (inputs, outputs, error codes).
- Define resource constraints (stack, heap, latency, determinism).
- Define platform assumptions (bare-metal / RTOS / SMP if applicable).

## Interfaces
- Input:
- Output:
- Error Handling:

## Reentrancy & Concurrency Notes
- Calling contexts: Task / ISR / SoftIRQ / SMP core (as applicable).
- Shared-state policy: no hidden mutable global state without explicit sync.
- Synchronization strategy: mutex / critical section / spinlock / lock-free (choose and justify).

## Acceptance Criteria
- [ ] Functional behavior matches problem statement.
- [ ] Concurrency safety documented and validated.
- [ ] Determinism/timing constraints measured and reported.

## Suggested Tests
1. Happy path correctness test.
2. Stress/preemption test with concurrent callers.
3. Fault-injection test (timeouts, invalid input, resource exhaustion).

## Notes
- Related roadmap item: [embedded_software_roadmap.md](../embedded_software_roadmap.md)

## Reference Implementation
- C source: [../../problems/embedded/E038_memory_pool_fixed_block/solution.c](../../problems/embedded/E038_memory_pool_fixed_block/solution.c)
