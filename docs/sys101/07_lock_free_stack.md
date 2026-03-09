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

## Solution Summary
The lock-free stack implementation uses a linked list with Compare-And-Swap (CAS) loops for thread-safe push and pop operations without mutexes. Each operation reads the current head, prepares the new state, and attempts to atomically update the head pointer, retrying on conflicts. The implementation must carefully handle the ABA problem where pointers can be reused.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/07_lock_free_stack/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Multi-threaded push/pop integrity**
- **Memory leak check (basic)**
- **Handling empty stack race**
