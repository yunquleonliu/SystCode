# E003: Memory Map Layout

## Objective
- Define specific memory regions for stack, heap, and shared memory in the linker file.

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

## Tutorial Walkthrough

### 1) Build a mental model first
- Think of **Memory Map Layout** as a system behavior problem before it is a coding problem.
- Clarify what is on the critical path: latency, determinism, memory footprint, and failure boundaries.
- Identify where this feature sits in the stack (driver/RTOS/core library/protocol path).

### 2) Implement in learning layers
- Start with a minimal correct version that is easy to reason about.
- Add correctness guards and edge-case handling.
- Add context-safety constraints (Task/ISR/SMP) explicitly.
- Finally optimize hot paths only after behavior is verified.

### 3) Validate like a firmware engineer
- Functional vectors: nominal + edge + invalid input behavior.
- Concurrency vectors: preemption windows, ISR/task overlap, lock usage correctness.
- Timing vectors: worst-case path and jitter-sensitive scenarios.

### 4) Readability and maintainability rules
- Keep API contracts explicit and side effects obvious.
- Avoid hidden global mutable state unless synchronization is documented.
- Prefer compiler intrinsics/standard primitives over fragile low-level tricks when equivalent.

## Common Mistakes
- Mixing correctness logic and optimization logic too early.
- Ignoring undefined behavior or architecture-specific corner cases.
- Assuming single-context execution in code that can run in ISR or SMP environment.
- Not defining observable acceptance criteria (what success looks like in tests/metrics).

## Reader Exercises (Optional)
1. Write one failing test first, then implement the minimum fix.
2. Add one performance-oriented variant and compare behavior + complexity.
3. Add one robustness hardening check and document the tradeoff.

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
- This spec serves as the detailed draft for E003.

## Notes
- Related roadmap item: [embedded_software_roadmap.md](/embedded101/embedded_software_roadmap.md)

## Implementation Overview

### Code Structure

**Dependencies**: stdio.h, stdint.h

**Key Functions**:
- ```c
  static int overlap(const MemoryRegion* first, const MemoryRegion* second) {
  ```
- ```c
  static int region_alloc(MemoryRegion* region, uint32_t bytes, uint32_t* out_addr) {
  ```
- ```c
  if (region->cursor + bytes > region->start + region->size) {
  ```
- ```c
  int main(void) {
  ```

**Test Logic**:
```c
MemoryRegion stack = {"stack", 0x2001C000u, 0x2000u, 0x2001C000u};
MemoryRegion heap = {"heap", 0x20010000u, 0xB000u, 0x20010000u};
MemoryRegion shared = {"shared", 0x2000F000u, 0x1000u, 0x2000F000u};
int layout_ok = !overlap(&stack, &heap) && !overlap(&stack, &shared) && !overlap(&heap, &shared);
uint32_t alloc1 = 0;
uint32_t alloc2 = 0;
int alloc_ok = region_alloc(&heap, 0x400, &alloc1) && region_alloc(&heap, 0x800, &alloc2);
printf("[E003] layout=%s alloc=%s first=0x%08X second=0x%08X\n",
layout_ok ? "PASS" : "FAIL",
alloc_ok ? "PASS" : "FAIL",
```


## Reference Implementation
- C source: [../../problems/embedded101/E003_memory_map_layout/solution.c](https://raw.githubusercontent.com/yunquleonliu/SystCode/main/problems/embedded101/E003_memory_map_layout/solution.c)
