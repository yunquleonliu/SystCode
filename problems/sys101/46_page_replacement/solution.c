/**
 * Problem 46: Page Replacement Algorithms
 * LRU and Clock-based page replacement.
 */
#include <stdio.h>
#include <stdlib.h>

#define FRAMES 4

typedef struct {
    int page;
    int timestamp;
} Frame;

typedef struct {
    Frame frames[FRAMES];
    int time;
} PageTable;

void pt_init(PageTable* pt) {
    for (int i = 0; i < FRAMES; i++) {
        pt->frames[i].page = -1;
    }
    pt->time = 0;
}

void access_page(PageTable* pt, int page) {
    for (int i = 0; i < FRAMES; i++) {
        if (pt->frames[i].page == page) {
            pt->frames[i].timestamp = pt->time++;
            printf("Page %d: HIT\n", page);
            return;
        }
    }
    
    int victim = 0;
    for (int i = 1; i < FRAMES; i++) {
        if (pt->frames[i].timestamp < pt->frames[victim].timestamp) {
            victim = i;
        }
    }
    
    if (pt->frames[victim].page != -1) {
        printf("Page %d: MISS (evicted page %d)\n", page, pt->frames[victim].page);
    } else {
        printf("Page %d: MISS\n", page);
    }
    
    pt->frames[victim].page = page;
    pt->frames[victim].timestamp = pt->time++;
}

int main() {
    printf("=== Page Replacement (LRU) ===\n\n");
    PageTable pt;
    pt_init(&pt);
    
    int refs[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
    for (int i = 0; i < 10; i++) {
        access_page(&pt, refs[i]);
    }
    return 0;
}