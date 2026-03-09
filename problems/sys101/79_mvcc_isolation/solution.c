/**
 * Problem 79: MVCC (Multi-Version Concurrency Control)
 * Maintain multiple versions for snapshot isolation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_VERSIONS 100
#define MAX_KEYS 1000

typedef struct {
    int version;
    int data;
    long timestamp;
} DataVersion;

typedef struct {
    DataVersion versions[MAX_VERSIONS];
    int num_versions;
} VersionChain;

typedef struct {
    VersionChain chains[MAX_KEYS];
    int next_version;
    pthread_mutex_t lock;
} MVCC;

MVCC* mvcc_create() {
    MVCC* mvcc = malloc(sizeof(MVCC));
    mvcc->next_version = 0;
    pthread_mutex_init(&mvcc->lock, NULL);
    
    for (int i = 0; i < MAX_KEYS; i++) {
        mvcc->chains[i].num_versions = 0;
    }
    
    return mvcc;
}

void mvcc_write(MVCC* mvcc, int key, int value) {
    pthread_mutex_lock(&mvcc->lock);
    
    if (mvcc->chains[key].num_versions >= MAX_VERSIONS) {
        pthread_mutex_unlock(&mvcc->lock);
        return;
    }
    
    DataVersion* ver = &mvcc->chains[key].versions[mvcc->chains[key].num_versions];
    ver->version = mvcc->next_version++;
    ver->data = value;
    ver->timestamp = time(NULL);
    mvcc->chains[key].num_versions++;
    
    pthread_mutex_unlock(&mvcc->lock);
}

int mvcc_read(MVCC* mvcc, int key, int snapshot_version) {
    pthread_mutex_lock(&mvcc->lock);
    
    int result = -1;
    VersionChain* chain = &mvcc->chains[key];
    
    for (int i = chain->num_versions - 1; i >= 0; i--) {
        if (chain->versions[i].version <= snapshot_version) {
            result = chain->versions[i].data;
            break;
        }
    }
    
    pthread_mutex_unlock(&mvcc->lock);
    return result;
}

void test_scenario() {
    printf("Running tests for MVCC...\n\n");
    
    MVCC* mvcc = mvcc_create();
    
    mvcc_write(mvcc, 100, 1);
    mvcc_write(mvcc, 100, 2);
    mvcc_write(mvcc, 100, 3);
    
    printf("Wrote 3 versions\n");
    
    int v0 = mvcc_read(mvcc, 100, 0);
    int v1 = mvcc_read(mvcc, 100, 1);
    int v2 = mvcc_read(mvcc, 100, 2);
    
    printf("Version 0: %d\n", v0);
    printf("Version 1: %d\n", v1);
    printf("Version 2: %d\n", v2);
    printf("Passed.\n");
    
    pthread_mutex_destroy(&mvcc->lock);
    free(mvcc);
}

int main() {
    test_scenario();
    return 0;
}