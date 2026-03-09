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

## Solution Summary
The LSM-Tree implementation maintains a sorted in-memory MemTable for writes with Write-Ahead Log (WAL) for durability. When the MemTable exceeds a threshold, it's sorted and flushed to disk as an immutable SSTable file. This write-optimized structure provides high write throughput by converting random writes into sequential disk operations.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/28_lsm_tree_storage/solution.c)**

## Testing Standards
- **Put retrieves correct Get**
- **Flush triggers when threshold met**
- **Data persists after flush**
