/**
 * Problem 27: Simple File System
 * In-memory filesystem with inodes and directory structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_BLOCKS 1000
#define BLOCK_SIZE 512
#define MAX_NAME 32
#define MAX_BLOCKS_PER_FILE 10

typedef enum { FILE_TYPE, DIR_TYPE } InodeType;

typedef struct {
    int inode_num;
    InodeType type;
    char name[MAX_NAME];
    int size;
    int blocks[MAX_BLOCKS_PER_FILE];
    int num_blocks;
    int parent_inode;
    time_t created;
    time_t modified;
} Inode;

typedef struct {
    char data[MAX_BLOCKS][BLOCK_SIZE];
    bool block_used[MAX_BLOCKS];
    Inode inodes[MAX_FILES];
    int num_inodes;
    int current_dir;
} FileSystem;

void fs_init(FileSystem* fs) {
    memset(fs, 0, sizeof(FileSystem));
    
    // Create root directory
    Inode* root = &fs->inodes[0];
    root->inode_num = 0;
    root->type = DIR_TYPE;
    strcpy(root->name, "/");
    root->parent_inode = 0;
    root->created = time(NULL);
    fs->num_inodes = 1;
    fs->current_dir = 0;
}

int fs_alloc_block(FileSystem* fs) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!fs->block_used[i]) {
            fs->block_used[i] = true;
            return i;
        }
    }
    return -1;
}

int fs_create_file(FileSystem* fs, const char* name) {
    if (fs->num_inodes >= MAX_FILES) return -1;
    
    Inode* inode = &fs->inodes[fs->num_inodes];
    inode->inode_num = fs->num_inodes;
    inode->type = FILE_TYPE;
    strncpy(inode->name, name, MAX_NAME - 1);
    inode->size = 0;
    inode->num_blocks = 0;
    inode->parent_inode = fs->current_dir;
    inode->created = time(NULL);
    inode->modified = inode->created;
    
    printf("Created file: %s (inode %d)\n", name, inode->inode_num);
    return fs->num_inodes++;
}

int fs_write(FileSystem* fs, int inode_num, const char* data, int len) {
    Inode* inode = &fs->inodes[inode_num];
    if (inode->type != FILE_TYPE) return -1;
    
    int written = 0;
    while (written < len) {
        if (inode->num_blocks >= MAX_BLOCKS_PER_FILE) break;
        
        int block = fs_alloc_block(fs);
        if (block < 0) break;
        
        int to_write = (len - written < BLOCK_SIZE) ? (len - written) : BLOCK_SIZE;
        memcpy(fs->data[block], data + written, to_write);
        inode->blocks[inode->num_blocks++] = block;
        written += to_write;
    }
    
    inode->size += written;
    inode->modified = time(NULL);
    return written;
}

int fs_read(FileSystem* fs, int inode_num, char* buf, int max_len) {
    Inode* inode = &fs->inodes[inode_num];
    if (inode->type != FILE_TYPE) return -1;
    
    int read = 0;
    for (int i = 0; i < inode->num_blocks && read < max_len; i++) {
        int to_read = (inode->size - read < BLOCK_SIZE) ? (inode->size - read) : BLOCK_SIZE;
        if (to_read > max_len - read) to_read = max_len - read;
        memcpy(buf + read, fs->data[inode->blocks[i]], to_read);
        read += to_read;
    }
    return read;
}

void fs_list(FileSystem* fs) {
    printf("\nDirectory listing (parent inode %d):\n", fs->current_dir);
    for (int i = 0; i < fs->num_inodes; i++) {
        Inode* inode = &fs->inodes[i];
        if (inode->parent_inode == fs->current_dir || i == 0) {
            printf("  %s %s (%d bytes)\n", 
                   inode->type == DIR_TYPE ? "DIR " : "FILE",
                   inode->name, inode->size);
        }
    }
}

int main() {
    printf("=== Simple File System ===\n\n");
    
    FileSystem fs;
    fs_init(&fs);
    
    int f1 = fs_create_file(&fs, "hello.txt");
    int f2 = fs_create_file(&fs, "data.bin");
    
    fs_write(&fs, f1, "Hello, World!", 13);
    fs_write(&fs, f2, "Binary data here...", 19);
    
    fs_list(&fs);
    
    char buf[100];
    int n = fs_read(&fs, f1, buf, 100);
    buf[n] = '\0';
    printf("\nRead from hello.txt: \"%s\"\n", buf);
    
    return 0;
}