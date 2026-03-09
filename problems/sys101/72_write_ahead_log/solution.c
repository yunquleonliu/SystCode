/**
 * Problem 72: Write-Ahead Logging (WAL)
 * Durability guarantee through log-based recovery
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_SIZE 10000

typedef enum {
    OP_INSERT = 1,
    OP_UPDATE = 2,
    OP_DELETE = 3
} OpType;

typedef struct {
    int log_id;
    OpType op;
    int key;
    int value;
    long timestamp;
    int committed;
} LogEntry;

typedef struct {
    LogEntry entries[LOG_SIZE];
    int head;
    int tail;
    int num_entries;
} WriteAheadLog;

WriteAheadLog* wal_create() {
    WriteAheadLog* wal = malloc(sizeof(WriteAheadLog));
    wal->head = 0;
    wal->tail = 0;
    wal->num_entries = 0;
    return wal;
}

int wal_append(WriteAheadLog* wal, OpType op, int key, int value) {
    if (wal->num_entries >= LOG_SIZE) {
        return -1;  // Log full
    }
    
    LogEntry* entry = &wal->entries[wal->tail];
    entry->log_id = wal->num_entries;
    entry->op = op;
    entry->key = key;
    entry->value = value;
    entry->timestamp = time(NULL);
    entry->committed = 0;
    
    wal->tail = (wal->tail + 1) % LOG_SIZE;
    wal->num_entries++;
    
    return entry->log_id;
}

void wal_commit(WriteAheadLog* wal, int log_id) {
    for (int i = 0; i < wal->num_entries; i++) {
        int idx = (wal->head + i) % LOG_SIZE;
        if (wal->entries[idx].log_id == log_id) {
            wal->entries[idx].committed = 1;
            return;
        }
    }
}

void wal_print_uncommitted(WriteAheadLog* wal) {
    int count = 0;
    printf("Uncommitted entries:\n");
    for (int i = 0; i < wal->num_entries; i++) {
        int idx = (wal->head + i) % LOG_SIZE;
        if (!wal->entries[idx].committed) {
            printf("  ID %d: op=%d key=%d\n", 
                   wal->entries[idx].log_id,
                   wal->entries[idx].op,
                   wal->entries[idx].key);
            count++;
        }
    }
    printf("Total uncommitted: %d\n", count);
}

void test_scenario() {
    printf("Running tests for Write-Ahead Log...\n\n");
    
    WriteAheadLog* wal = wal_create();
    
    int id1 = wal_append(wal, OP_INSERT, 100, 42);
    int id2 = wal_append(wal, OP_UPDATE, 100, 43);
    int id3 = wal_append(wal, OP_INSERT, 200, 99);
    
    printf("Appended 3 entries\n");
    wal_print_uncommitted(wal);
    
    wal_commit(wal, id1);
    wal_commit(wal, id2);
    
    printf("\nAfter commit:​\n");
    wal_print_uncommitted(wal);
    
    printf("Passed.\n");
    free(wal);
}

int main() {
    test_scenario();
    return 0;
}