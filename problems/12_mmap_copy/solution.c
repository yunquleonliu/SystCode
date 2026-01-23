#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

// Function to copy a file using mmap
void mmap_copy(const char *src_path, const char *dst_path) {
    int fdin, fdout;
    struct stat sbuf;
    char *src, *dst;

    if ((fdin = open(src_path, O_RDONLY)) < 0) {
        perror("open src");
        exit(1);
    }
    if (fstat(fdin, &sbuf) < 0) {
        perror("fstat");
        exit(1);
    }
    if ((fdout = open(dst_path, O_RDWR | O_CREAT | O_TRUNC, 0664)) < 0) {
        perror("open dst");
        exit(1);
    }
    // Resize destination file
    if (ftruncate(fdout, sbuf.st_size) < 0) {
        perror("ftruncate");
        exit(1);
    }

    // mmap source (Read-only)
    if ((src = mmap(0, sbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED) {
        perror("mmap src");
        exit(1);
    }

    // mmap destination (Read/Write)
    if ((dst = mmap(0, sbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED) {
        perror("mmap dst");
        exit(1);
    }

    // Perform the copy (Memory to Memory)
    memcpy(dst, src, sbuf.st_size);

    // Cleanup
    munmap(src, sbuf.st_size);
    munmap(dst, sbuf.st_size);
    close(fdin);
    close(fdout);
}

void solution() {
}

int main(int argc, char** argv) {
    const char* src_file = "test_source.tmp";
    const char* dst_file = "test_dest.tmp";

    // Setup: Create a file with content
    FILE* fp = fopen(src_file, "w");
    if(!fp) { perror("fopen"); return 1; }
    fprintf(fp, "This is a test of mmap file copy.\nLines of text.");
    fclose(fp);

    printf("Copying %s to %s using mmap...\n", src_file, dst_file);
    mmap_copy(src_file, dst_file);

    // Verification
    char buffer[1024];
    fp = fopen(dst_file, "r");
    if(!fp) { 
        printf("Failed to open destination file!\n");
        return 1;
    }
    size_t len = fread(buffer, 1, sizeof(buffer)-1, fp);
    buffer[len] = '\0';
    fclose(fp);

    printf("Destination content: %s\n", buffer);
    if (strstr(buffer, "This is a test of mmap file copy.")) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed\n");
    }

    // Teardown
    unlink(src_file);
    unlink(dst_file);

    return 0;
}
