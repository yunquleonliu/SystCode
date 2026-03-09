/**
 * Problem 45: FUSE Filesystem
 * Userspace filesystem operations.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100

typedef struct {
    char name[64];
    char data[1024];
    int size;
    int is_dir;
} FileEntry;

typedef struct {
    FileEntry files[MAX_FILES];
    int count;
} FUSEFS;

FUSEFS* fs_create() {
    FUSEFS* fs = calloc(1, sizeof(FUSEFS));
    strcpy(fs->files[0].name, "/");
    fs->files[0].is_dir = 1;
    fs->count = 1;
    return fs;
}

int fs_create_file(FUSEFS* fs, const char* name) {
    if (fs->count >= MAX_FILES) return -1;
    strcpy(fs->files[fs->count].name, name);
    fs->files[fs->count].is_dir = 0;
    printf("created %s\n", name);
    return fs->count++;
}

int fs_write(FUSEFS* fs, int idx, const char* data, int len) {
    if (idx >= fs->count) return -1;
    int to_write = (len < 1024) ? len : 1024;
    memcpy(fs->files[idx].data, data, to_write);
    fs->files[idx].size = to_write;
    printf("wrote %d bytes to %s\n", to_write, fs->files[idx].name);
    return to_write;
}

int main() {
    printf("=== FUSE Filesystem ===\n\n");
    FUSEFS* fs = fs_create();
    int f1 = fs_create_file(fs, "/hello.txt");
    fs_write(fs, f1, "Hello, FUSE!", 12);
    return 0;
}