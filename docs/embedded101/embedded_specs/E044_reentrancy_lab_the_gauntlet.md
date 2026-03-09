# E044: Reentrancy Lab (The Gauntlet)

## Objective
- Create a driver that fails under preemption (race condition), then fix it using Mutex, Critical Sections, and Lock-Free methods.

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

## Existing Detailed Draft
- See [Reentrancy Lab detailed problem](../embedded_reentrancy_lab.md).

## Notes
- Related roadmap item: [embedded_software_roadmap.md](../embedded_software_roadmap.md)

## Reference Implementation
- C source: [../../problems/embedded101/embedded/E044_reentrancy_lab_the_gauntlet/solution.c](https://github.com/yunquleonliu/SystCode/blob/main/problems/embedded101/embedded/E044_reentrancy_lab_the_gauntlet/solution.c)
