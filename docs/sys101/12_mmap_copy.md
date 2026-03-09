# Problem 12: Mmap Copy

## Description
Use memory mapping (mmap) to implement a high-performance file copy utility.

## Learning Objectives
- mmap/munmap
- Virtual memory
- OS Page Cache

## Implementation Steps
1. Review the header files (if any).
2. Define necessary data structures.
3. Implement the core logic functions.
4. Handle edge cases (null pointers, overflows).

## Pseudocode Hint
```text
copy_file(src_fd, dst_fd, size):
         src_ptr = mmap(src_fd, READ)
         dst_ptr = mmap(dst_fd, WRITE) // truncate dst first
         
         memcpy(dst_ptr, src_ptr, size)
         
         munmap(src_ptr)
         munmap(dst_ptr)
```


## Why This Problem Matters
- **Mmap Copy** appears in real systems as a building block for reliability, performance, or scalability.
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
The memory-mapped file copy implementation maps both source and destination files into the process's virtual address space using `mmap`, then performs a simple `memcpy` between mapped regions. This approach leverages the OS page cache for efficient I/O and lazy loading, handling large files without loading them entirely into RAM.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/12_mmap_copy/solution.c)**

## Testing Standards
Your solution must pass the following test scenarios:
- **Copy large file (> RAM size ideally, or chunks)**
- **File integrity check (hash)**
- **Permissions validation**
