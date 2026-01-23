# Problem 8: Thread Pool

## Description
Build a thread pool that manages a fixed number of worker threads to execute tasks.

## Learning Objectives
- Condition variables
- Mutexes
- Producer-Consumer queues

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
queue: methods to enqueue/dequeue tasks
     mutex, condition_var
     
     worker_thread():
         while true:
             lock(mutex)
             while queue is empty and running:
                 wait(condition_var, mutex)
             if not running and queue empty: break
             task = queue.dequeue()
             unlock(mutex)
             execute(task)
```

## Testing Standards
Your solution must pass the following test scenarios:
- **Submit N tasks to M threads (N > M)**
- **Verify all tasks complete**
- **Graceful shutdown**
