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

## Solution Summary
The thread pool maintains a fixed number of worker threads and a task queue protected by a mutex. Workers wait on a condition variable when the queue is empty, wake up when tasks are added, and execute tasks sequentially. The pool supports graceful shutdown by signaling all workers to exit after completing pending tasks.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/08_thread_pool/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Submit N tasks to M threads (N > M)**
- **Verify all tasks complete**
- **Graceful shutdown**
