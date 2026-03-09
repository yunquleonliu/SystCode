# Problem: Reentrancy Lab (The Gauntlet)

## Description

In an embedded system, a driver function (like `uart_write`) can be called from:

1.  Background task (Main loop)
2.  High-priority task (Preempts main loop)
3.  Interrupt Service Routine (ISR) (Preempts high-priority task)
4.  Another core (SMP)

If these calls overlap and access shared resources (global variables, hardware registers) without protection, **data corruption** or **hardware lockup** occurs.

This challenge tasks you to:

1.  **Analyze** the provided `unsafe_driver.c` which simulates a UART transmission driver with a shared internal buffer and index.
2.  **Break It**: Write a test case in `main()` that spawns multiple threads (simulating tasks) to call `uart_write` concurrently and demonstrate data corruption (garbled output).
3.  **Fix It**: Implement three different versions of `uart_write` using:
    *   **Mutex**: For Task-to-Task protection.
    *   **Critical Section (Interrupt Disabling)**: For Task-to-ISR protection.
    *   **Lock-Free (Atomic/Local)**: For wait-free or re-entrant safe implementation.

## Requirements

*   **Inputs**: A shared `char buffer[128]` and `int head_idx`.
*   **Threads**: At least 2 concurrent writers.
*   **Verification**: The output stream must be coherent (no interleaved characters from different messages).

## Hint

*   Use `pthread_mutex_t` for the mutex solution.
*   Use a global flag or simulated `cli()` / `sei()` function for critical sections.
*   For the lock-free version, consider if you *need* a global buffer at all, or if passing a pointer directly to "hardware" (simulated via `write(STDOUT)`) works better.