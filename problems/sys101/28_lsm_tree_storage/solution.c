/**
 * Problem 28: LSM-Tree Storage Engine
 * Log-Structured Merge Tree for write-optimized storage.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MEMTABLE_SIZE 5
#define MAX_LEVELS 3
#define MAX_ENTRIES 100

typedef struct {
    char key[32];
    char value[64];
    bool deleted;
} Entry;

typedef struct {
    Entry entries[MEMTABLE_SIZE];
    int count;
} Memtable;

typedef struct {
    Entry entries[MAX_ENTRIES];
    int count;
} SSTable;

typedef struct {
    Memtable* memtable;
    SSTable* levels[MAX_LEVELS];
} LSMTree;

int entry_compare(const void* a, const void* b) {
    return strcmp(((Entry*)a)->key, ((Entry*)b)->key);
}

LSMTree* lsm_create() {
    LSMTree* tree = calloc(1, sizeof(LSMTree));
    tree->memtable = calloc(1, sizeof(Memtable));
    for (int i = 0; i < MAX_LEVELS; i++) {
        tree->levels[i] = calloc(1, sizeof(SSTable));
    }
    return tree;
}

void lsm_flush_memtable(LSMTree* tree) {
    printf("Flushing memtable to Level 0 SSTable...\n");
    
    // Sort memtable
    qsort(tree->memtable->entries, tree->memtable->count, sizeof(Entry), entry_compare);
    
    // Merge into level 0
    SSTable* l0 = tree->levels[0];
    for (int i = 0; i < tree->memtable->count; i++) {
        if (l0->count < MAX_ENTRIES) {
            l0->entries[l0->count++] = tree->memtable->entries[i];
        }
    }
    
    tree->memtable->count = 0;
}

void lsm_put(LSMTree* tree, const char* key, const char* value) {
    Memtable* mt = tree->memtable;
    
    // Check if key exists in memtable
    for (int i = 0; i < mt->count; i++) {
        if (strcmp(mt->entries[i].key, key) == 0) {
            strncpy(mt->entries[i].value, value, 63);
            mt->entries[i].deleted = false;
            return;
        }
    }
    
    // Add new entry
    if (mt->count >= MEMTABLE_SIZE) {
        lsm_flush_memtable(tree);
    }
    
    Entry* e = &mt->entries[mt->count++];
    strncpy(e->key, key, 31);
    strncpy(e->value, value, 63);
    e->deleted = false;
    
    printf("PUT %s = %s\n", key, value);
}

const char* lsm_get(LSMTree* tree, const char* key) {
    // Search memtable first (most recent)
    for (int i = tree->memtable->count - 1; i >= 0; i--) {
        if (strcmp(tree->memtable->entries[i].key, key) == 0) {
            if (tree->memtable->entries[i].deleted) return NULL;
            return tree->memtable->entries[i].value;
        }
    }
    
    // Search SSTables (level 0 to N)
    for (int l = 0; l < MAX_LEVELS; l++) {
        SSTable* sst = tree->levels[l];
        for (int i = sst->count - 1; i >= 0; i--) {
            if (strcmp(sst->entries[i].key, key) == 0) {
                if (sst->entries[i].deleted) return NULL;
                return sst->entries[i].value;
            }
        }
    }
    
    return NULL;
}

void lsm_delete(LSMTree* tree, const char* key) {
    // Tombstone marker
    Memtable* mt = tree->memtable;
    if (mt->count >= MEMTABLE_SIZE) {
        lsm_flush_memtable(tree);
    }
    
    Entry* e = &mt->entries[mt->count++];
    strncpy(e->key, key, 31);
    e->value[0] = '\0';
    e->deleted = true;
    
    printf("DELETE %s (tombstone)\n", key);
}

void lsm_free(LSMTree* tree) {
    free(tree->memtable);
    for (int i = 0; i < MAX_LEVELS; i++) {
        free(tree->levels[i]);
    }
    free(tree);
}

int main() {
    printf("=== LSM-Tree Storage ===\n\n");
    
    LSMTree* tree = lsm_create();
    
    lsm_put(tree, "user:1", "Alice");
    lsm_put(tree, "user:2", "Bob");
    lsm_put(tree, "user:3", "Charlie");
    
    printf("\nGET user:2 = %s\n", lsm_get(tree, "user:2"));
    
    lsm_put(tree, "user:4", "Diana");
    lsm_put(tree, "user:5", "Eve");  // Triggers flush
    lsm_put(tree, "user:6", "Frank");
    
    printf("\nGET user:1 = %s\n", lsm_get(tree, "user:1"));
    
    lsm_delete(tree, "user:2");
    printf("GET user:2 = %s\n", lsm_get(tree, "user:2") ? lsm_get(tree, "user:2") : "(deleted)");
    
    lsm_free(tree);
    return 0;
}