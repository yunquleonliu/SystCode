# Problem 14: Ring Buffer

## Description
Implement a lock-free Single-Producer Single-Consumer (SPSC) circular buffer.

## Learning Objectives
- Modulo arithmetic
- Memory barriers
- Index management

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct RingBuffer {
         buffer[SIZE]
         head (write_idx)
         tail (read_idx)
     }
     
     write(item):
         if (head + 1) % SIZE == tail: return FULL
         buffer[head] = item
         head = (head + 1) % SIZE
         
     read():
         if tail == head: return EMPTY
         item = buffer[tail]
         tail = (tail + 1) % SIZE
         return item
```


## Why This Problem Matters
- **Ring Buffer** appears in real systems as a building block for reliability, performance, or scalability.
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
The lock-free ring buffer uses separate head (write) and tail (read) indices with modulo arithmetic to create a circular queue. The implementation detects full buffer when `(head + 1) % SIZE == tail` and empty buffer when `head == tail`, providing efficient FIFO operations for single-producer single-consumer scenarios without locking.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/14_ring_buffer/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **FIFO ordering**
- **Full buffer detection**
- **Empty buffer detection**
