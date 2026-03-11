# E012: UART Polling Driver

## Objective
- Write a simple blocking UART transmitter and receiver.

## Background
- Module: Peripheral Driver Development (15 Problems)
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
- Think of **UART Polling Driver** as a system behavior problem before it is a coding problem.
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
- This spec serves as the detailed draft for E012.

## Notes
- Related roadmap item: [embedded_software_roadmap.md](/embedded101/embedded_software_roadmap.md)

## Implementation Overview

### Code Structure

**Dependencies**: string.h, stdio.h

**Key Functions**:
- ```c
  static void uart_init(Uart* uart) { memset(uart, 0, sizeof(*uart)); }
  ```
- ```c
  static void uart_polling_send(Uart* uart, const char* text) {
  ```
- ```c
  static int uart_polling_recv(Uart* uart, char* out) {
  ```
- ```c
  int main(void) {
  ```

**Test Logic**:
```c
uart.rx_fifo[uart.rx_tail++] = 'O';
uart.rx_fifo[uart.rx_tail++] = 'K';
char first = '\0';
char second = '\0';
int got1 = uart_polling_recv(&uart, &first);
int got2 = uart_polling_recv(&uart, &second);
int ok = (uart.tx_len == 5u) && got1 && got2 && first == 'O' && second == 'K';
printf("[E012] tx=%.*s rx=%c%c %s\n", (int)uart.tx_len, uart.tx_log, first, second, ok ? "PASS" : "FAIL");
return ok ? 0 : 1;
```


## Reference Implementation
- C source: [../../problems/embedded101/E012_uart_polling_driver/solution.c](https://raw.githubusercontent.com/yunquleonliu/SystCode/main/problems/embedded101/E012_uart_polling_driver/solution.c)
