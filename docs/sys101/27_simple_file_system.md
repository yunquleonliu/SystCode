# Problem 27: Simple File System

## Description
Implement a basic Inode-based virtual file system on top of a large binary file.

## Learning Objectives
- Superblock
- Inodes
- Bitmaps (Allocation)

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.

## Pseudocode Hint
```text
mkfs(file):
         write_superblock()
         init_bitmaps()
         
     create_file(name):
         inode_idx = alloc_inode()
         dir_add(name, inode_idx)
         
     write(fd, data):
         block = alloc_block()
         inode.blocks.append(block)
         disk_write(block, data)
```


## Why This Problem Matters
- **Simple File System** appears in real systems as a building block for reliability, performance, or scalability.
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
The simple file system implements an inode-based structure with a superblock, inode table, and block bitmaps on a virtual disk file. It allocates inodes and data blocks using bitmaps, maintains directory entries linking names to inode numbers, and supports basic file operations (create, write, read) with persistence across sessions.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/27_simple_file_system/solution.c)**

## Testing Standards
- **Create and list files**
- **Write data and Read data back**
- **Persistence (reload fs)**
