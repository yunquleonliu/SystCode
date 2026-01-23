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

## Testing Standards
Your solution must pass the following test scenarios:
- **Copy large file (> RAM size ideally, or chunks)**
- **File integrity check (hash)**
- **Permissions validation**
