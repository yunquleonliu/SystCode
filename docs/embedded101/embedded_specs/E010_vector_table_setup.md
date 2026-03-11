# E010: Vector Table Setup

## Objective
- Define and relocate an interrupt vector table in C.

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
- Think of **Vector Table Setup** as a system behavior problem before it is a coding problem.
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
- This spec serves as the detailed draft for E010.

## Notes
- Related roadmap item: [embedded_software_roadmap.md](/embedded101/embedded_software_roadmap.md)

## Implementation Overview

### Code Structure

**Dependencies**: stdio.h

**Key Functions**:
- ```c
  static void default_handler(void) {
  ```
- ```c
  static void timer_handler(void) {
  ```
- ```c
  static void uart_handler(void) {
  ```
- ```c
  static void vector_invoke(IsrHandler* table, int irq) {
  ```
- ```c
  if (irq >= 0 && irq < VECTOR_COUNT && table[irq] != NULL) {
  ```

**Test Logic**:
```c
for (int index = 0; index < VECTOR_COUNT; ++index) {
flash_vector[index] = default_handler;
ram_vector[index] = default_handler;
flash_vector[3] = timer_handler;
flash_vector[4] = uart_handler;
for (int index = 0; index < VECTOR_COUNT; ++index) {
ram_vector[index] = flash_vector[index];
vector_invoke(ram_vector, 3);
vector_invoke(ram_vector, 4);
vector_invoke(ram_vector, 7);
```


## Reference Implementation
- C source: [../../problems/embedded101/E010_vector_table_setup/solution.c](https://raw.githubusercontent.com/yunquleonliu/SystCode/main/problems/embedded101/E010_vector_table_setup/solution.c)
