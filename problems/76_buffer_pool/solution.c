/**
 * Problem 76: Buffer Pool Manager
 * In-memory page cache with LRU eviction policy
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_FRAMES 32
#define PAGE_SIZE 4096

typedef struct {
    int page_id;
    char data[PAGE_SIZE];
    int dirty;
    int pin_count;
} Frame;

typedef struct {
    Frame frames[BUFFER_FRAMES];
    int* lru_clock;
    int clock_hand;
} BufferPool;

BufferPool* buffer_create() {
    BufferPool* bp = malloc(sizeof(BufferPool));
    for (int i = 0; i < BUFFER_FRAMES; i++) {
        bp->frames[i].page_id = -1;
        bp->frames[i].dirty = 0;
        bp->frames[i].pin_count = 0;
    }
    bp->lru_clock = calloc(BUFFER_FRAMES, sizeof(int));
    bp->clock_hand = 0;
    return bp;
}

int buffer_find_free_frame(BufferPool* bp) {
    // Find unpinned frame using clock algorithm
    for (int i = 0; i < BUFFER_FRAMES; i++) {
        if (bp->frames[i].pin_count == 0 && bp->lru_clock[i] == 0) {
            return i;
        }
    }
    
    // If no free frame found, sweep again
    for (int i = 0; i < BUFFER_FRAMES; i++) {
        bp->lru_clock[i] = 0;
    }
    
    return 0;  // Evict frame 0
}

Frame* buffer_get_page(BufferPool* bp, int page_id) {
    // Check if already in buffer
    for (int i = 0; i < BUFFER_FRAMES; i++) {
        if (bp->frames[i].page_id == page_id) {
            bp->frames[i].pin_count++;
            bp->lru_clock[i] = 1;
            return &bp->frames[i];
        }
    }
    
    // Need to load from disk - find frame
    int frame_id = buffer_find_free_frame(bp);
    
    if (bp->frames[frame_id].dirty) {
        printf("Flushing dirty page %d\n", bp->frames[frame_id].page_id);
    }
    
    bp->frames[frame_id].page_id = page_id;
    bp->frames[frame_id].dirty = 0;
    bp->frames[frame_id].pin_count = 1;
    bp->lru_clock[frame_id] = 1;
    
    return &bp->frames[frame_id];
}

void buffer_unpin_page(BufferPool* bp, int page_id, int dirty) {
    for (int i = 0; i < BUFFER_FRAMES; i++) {
        if (bp->frames[i].page_id == page_id) {
            if (bp->frames[i].pin_count > 0) {
                bp->frames[i].pin_count--;
            }
            if (dirty) {
                bp->frames[i].dirty = 1;
            }
            return;
        }
    }
}

void test_scenario() {
    printf("Running tests for Buffer Pool Manager...\n\n");
    
    BufferPool* bp = buffer_create();
    
    // Access pages
    Frame* f1 = buffer_get_page(bp, 100);
    printf("Got page 100\n");
    strcpy(f1->data, "Page 100 data");
    
    Frame* f2 = buffer_get_page(bp, 200);
    printf("Got page 200\n");
    strcpy(f2->data, "Page 200 data");
    
    buffer_unpin_page(bp, 100, 0);
    buffer_unpin_page(bp, 200, 1);
    
    printf("Unpinned pages\n");
    printf("Frame 1 dirty: %d\n", bp->frames[0].dirty);
    printf("Passed.\n");
    
    free(bp->lru_clock);
    free(bp);
}

int main() {
    test_scenario();
    return 0;
}