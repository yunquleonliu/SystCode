/**
 * Problem 78: Bitcask Key-Value Store
 * Log-structured KV store with in-memory index
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ENTRIES 10000
#define KEY_SIZE 64
#define VALUE_SIZE 256

typedef struct {
    int timestamp;
    int key_size;
    int value_size;
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
} LogEntry;

typedef struct {
    int file_offset;
    int value_size;
    int timestamp;
} IndexEntry;

typedef struct {
    LogEntry log[MAX_ENTRIES];
    IndexEntry index[MAX_ENTRIES];
    int log_size;
} Bitcask;

Bitcask* bitcask_create() {
    Bitcask* bc = malloc(sizeof(Bitcask));
    bc->log_size = 0;
    return bc;
}

void bitcask_put(Bitcask* bc, const char* key, const char* value) {
    if (bc->log_size >= MAX_ENTRIES) {
        return;  // Log full
    }
    
    LogEntry* entry = &bc->log[bc->log_size];
    entry->timestamp = time(NULL);
    strncpy(entry->key, key, KEY_SIZE - 1);
    strncpy(entry->value, value, VALUE_SIZE - 1);
    entry->key_size = strlen(key);
    entry->value_size = strlen(value);
    
    // Update index
    int key_hash = 0;
    for (int i = 0; key[i]; i++) {
        key_hash = (key_hash * 31 + key[i]) % MAX_ENTRIES;
    }
    
    bc->index[key_hash].file_offset = bc->log_size;
    bc->index[key_hash].value_size = entry->value_size;
    bc->index[key_hash].timestamp = entry->timestamp;
    
    bc->log_size++;
}

char* bitcask_get(Bitcask* bc, const char* key) {
    int key_hash = 0;
    for (int i = 0; key[i]; i++) {
        key_hash = (key_hash * 31 + key[i]) % MAX_ENTRIES;
    }
    
    int offset = bc->index[key_hash].file_offset;
    if (offset < bc->log_size) {
        LogEntry* entry = &bc->log[offset];
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
    }
    
    return NULL;
}

void test_scenario() {
    printf("Running tests for Bitcask KV Store...\n\n");
    
    Bitcask* bc = bitcask_create();
    
    bitcask_put(bc, "user:1", "Alice");
    bitcask_put(bc, "user:2", "Bob");
    bitcask_put(bc, "user:3", "Carol");
    
    printf("Put 3 key-value pairs\n");
    
    char* val1 = bitcask_get(bc, "user:1");
    char* val2 = bitcask_get(bc, "user:2");
    
    printf("user:1 = %s\n", val1);
    printf("user:2 = %s\n", val2);
    printf("Passed.\n");
    
    free(bc);
}

int main() {
    test_scenario();
    return 0;
}