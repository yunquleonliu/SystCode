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

## Testing Standards
Your solution must pass the following test scenarios:
- **Multi-threaded push/pop integrity**
- **Memory leak check (basic)**
- **Handling empty stack race**
