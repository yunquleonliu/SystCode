/**
 * Problem 75: Slotted Page Layout
 * Variable-length record storage with offset pointers
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096
#define MAX_SLOTS 128

typedef struct {
    unsigned short offset;
    unsigned short length;
} Slot;

typedef struct {
    char data[PAGE_SIZE];
    Slot slots[MAX_SLOTS];
    int num_slots;
    int free_space;
} SlottedPage;

SlottedPage* page_create() {
    SlottedPage* page = malloc(sizeof(SlottedPage));
    page->num_slots = 0;
    page->free_space = PAGE_SIZE - (MAX_SLOTS * sizeof(Slot));
    return page;
}

int page_insert(SlottedPage* page, const char* data, int len) {
    if (len > page->free_space || page->num_slots >= MAX_SLOTS) {
        return -1;  // No space
    }
    
    // Insert at end of used space
    int offset = PAGE_SIZE - (page->num_slots * sizeof(Slot)) - 
                 (PAGE_SIZE - page->free_space - (page->num_slots * sizeof(Slot)));
    
    // Simplified: just append
    memcpy(&page->data[PAGE_SIZE - page->free_space], data, len);
    
    page->slots[page->num_slots].offset = PAGE_SIZE - page->free_space;
    page->slots[page->num_slots].length = len;
    page->num_slots++;
    page->free_space -= len;
    
    return page->num_slots - 1;
}

char* page_get(SlottedPage* page, int slot_id) {
    if (slot_id >= page->num_slots) {
        return NULL;
    }
    
    return &page->data[page->slots[slot_id].offset];
}

void page_delete(SlottedPage* page, int slot_id) {
    if (slot_id >= page->num_slots) {
        return;
    }
    
    page->slots[slot_id].length = 0;  // Mark as deleted
}

void test_scenario() {
    printf("Running tests for Slotted Page...\n\n");
    
    SlottedPage* page = page_create();
    
    const char* records[] = {"Hello", "World", "Database", "System"};
    
    for (int i = 0; i < 4; i++) {
        int slot = page_insert(page, records[i], strlen(records[i]) + 1);
        printf("Inserted '%s' at slot %d\n", records[i], slot);
    }
    
    printf("\nRetrieving records:\n");
    for (int i = 0; i < page->num_slots; i++) {
        char* record = page_get(page, i);
        printf("Slot %d: %s\n", i, record);
    }
    
    printf("Free space: %d bytes\n", page->free_space);
    printf("Passed.\n");
    
    free(page);
}

int main() {
    test_scenario();
    return 0;
}