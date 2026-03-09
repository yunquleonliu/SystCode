# Problem 7: Lock-free Stack

## Description
Design a concurrent stack data structure that requires no mutexes.

## Learning Objectives
- Compare-And-Swap loops
- ABA problem
- Linked lists

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
struct Node { next, data }
     struct Stack { head }
     
     push(data):
         new_node = allocate(Node{data})
         loop:
             old_head = head
             new_node.next = old_head
             if CAS(&head, old_head, new_node):
                 break
                 
     pop():
         loop:
             old_head = head
             if old_head == NULL: return empty
             next_node = old_head.next
             if CAS(&head, old_head, next_node):
                 return old_head.data
```


## Why This Problem Matters
- **Lock-free Stack** appears in real systems as a building block for reliability, performance, or scalability.
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
The lock-free stack implementation uses a linked list with Compare-And-Swap (CAS) loops for thread-safe push and pop operations without mutexes. Each operation reads the current head, prepares the new state, and attempts to atomically update the head pointer, retrying on conflicts. The implementation must carefully handle the ABA problem where pointers can be reused.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/07_lock_free_stack/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Multi-threaded push/pop integrity**
- **Memory leak check (basic)**
- **Handling empty stack race**
