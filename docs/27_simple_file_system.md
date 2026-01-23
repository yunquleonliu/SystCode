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

## Solution Summary
The simple file system implements an inode-based structure with a superblock, inode table, and block bitmaps on a virtual disk file. It allocates inodes and data blocks using bitmaps, maintains directory entries linking names to inode numbers, and supports basic file operations (create, write, read) with persistence across sessions.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/27_simple_file_system/solution.c)**

## Testing Standards
- **Create and list files**
- **Write data and Read data back**
- **Persistence (reload fs)**
