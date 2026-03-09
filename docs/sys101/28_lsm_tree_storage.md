# Problem 28: LSM-Tree Storage

## Description
Implement the write path of a Log-Structured Merge Tree (MemTable + simple SSTable flush).

## Learning Objectives
- Write-Ahead Log
- MemTable (Sorted)
- SSTable (Immutable)

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.

## Pseudocode Hint
```text
put(key, value):
         append_to_wal(key, value)
         memtable.insert(key, value)
         if memtable.size > THRESHOLD:
             flush_to_disk()
     
     flush_to_disk():
         sort(memtable)
         write_sstable(memtable)
         memtable.clear()
```


## Why This Problem Matters
- **LSM-Tree Storage** appears in real systems as a building block for reliability, performance, or scalability.
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
The LSM-Tree implementation maintains a sorted in-memory MemTable for writes with Write-Ahead Log (WAL) for durability. When the MemTable exceeds a threshold, it's sorted and flushed to disk as an immutable SSTable file. This write-optimized structure provides high write throughput by converting random writes into sequential disk operations.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/28_lsm_tree_storage/solution.c)**

## Testing Standards
- **Put retrieves correct Get**
- **Flush triggers when threshold met**
- **Data persists after flush**
