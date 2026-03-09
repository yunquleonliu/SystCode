# E007: Endianness Handling

## Objective
- Write code to detect and handle data endianness dynamically or statically during compile time.

## Background
- Module: Bare Metal Essentials & Architecture (10 Problems)
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
- C source: [../../problems/embedded101/E007_endianness_handling/solution.c](https://github.com/yunquleonliu/SystCode/blob/main/problems/embedded101/E007_endianness_handling/solution.c)
