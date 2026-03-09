/**
 * Problem 85: MapReduce Framework
 * Distributed data processing pattern
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    int value;
} KVPair;

typedef struct {
    KVPair pairs[1000];
    int count;
} Mapper;

typedef struct {
    char key[64];
    int values[100];
    int count;
} ReducerGroup;

Mapper* mapreduce_map(int* data, int len) {
    Mapper* mapper = malloc(sizeof(Mapper));
    mapper->count = 0;
    
    for (int i = 0; i < len; i++) {
        sprintf(mapper->pairs[mapper->count].key, "key_%d", data[i] % 10);
        mapper->pairs[mapper->count].value = 1;
        mapper->count++;
    }
    
    return mapper;
}

ReducerGroup* mapreduce_shuffle_and_sort(Mapper* mapper) {
    ReducerGroup* groups = malloc(sizeof(ReducerGroup) * 10);
    
    for (int i = 0; i < 10; i++) {
        sprintf(groups[i].key, "key_%d", i);
        groups[i].count = 0;
    }
    
    for (int i = 0; i < mapper->count; i++) {
        int idx = atoi(&mapper->pairs[i].key[4]);
        groups[idx].values[groups[idx].count++] = mapper->pairs[i].value;
    }
    
    return groups;
}

int mapreduce_reduce(ReducerGroup* group) {
    int sum = 0;
    for (int i = 0; i < group->count; i++) {
        sum += group->values[i];
    }
    return sum;
}

void test_scenario() {
    printf("Running tests for MapReduce...\n\n");
    
    int data[] = {1, 2, 3, 4, 5, 11, 12, 13, 14, 15};
    
    // Map phase
    Mapper* mapper = mapreduce_map(data, 10);
    printf("Map phase: %d pairs emitted\n", mapper->count);
    
    // Shuffle & Sort
    ReducerGroup* groups = mapreduce_shuffle_and_sort(mapper);
    
    // Reduce phase
    printf("\nReduce results:\n");
    for (int i = 0; i < 10; i++) {
        if (groups[i].count > 0) {
            int result = mapreduce_reduce(&groups[i]);
            printf("  %s: %d\n", groups[i].key, result);
        }
    }
    
    printf("Passed.\n");
    free(mapper);
    free(groups);
}

int main() {
    test_scenario();
    return 0;
}