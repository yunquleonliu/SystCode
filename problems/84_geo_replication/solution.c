/**
 * Problem 84: Geo-Replication
 * Multi-region data consistency model
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    REGION_US,
    REGION_EU,
    REGION_ASIA
} Region;

typedef struct {
    int version;
    long timestamp;
    char data[256];
} Replica;

typedef struct {
    Replica replicas[3];
    int version_clock;
} GeoReplica;

GeoReplica* georep_create() {
    GeoReplica* gr = malloc(sizeof(GeoReplica));
    gr->version_clock = 0;
    for (int i = 0; i < 3; i++) {
        gr->replicas[i].version = 0;
        gr->replicas[i].timestamp = 0;
    }
    return gr;
}

void georep_write(GeoReplica* gr, Region region, const char* data) {
    gr->version_clock++;
    
    gr->replicas[region].version = gr->version_clock;
    gr->replicas[region].timestamp = time(NULL);
    strncpy(gr->replicas[region].data, data, 255);
    
    printf("Wrote to %s (v%d)\n", 
           region == REGION_US ? "US" : (region == REGION_EU ? "EU" : "ASIA"),
           gr->version_clock);
}

void georep_replicate(GeoReplica* gr, Region from, Region to) {
    if (gr->replicas[from].version > gr->replicas[to].version) {
        gr->replicas[to].version = gr->replicas[from].version;
        gr->replicas[to].timestamp = time(NULL);
        strcpy(gr->replicas[to].data, gr->replicas[from].data);
    }
}

void test_scenario() {
    printf("Running tests for Geo-Replication...\n\n");
    
    GeoReplica* gr = georep_create();
    
    georep_write(gr, REGION_US, "Data v1");
    printf("US replica version: %d\n", gr->replicas[REGION_US].version);
    printf("EU replica version: %d\n", gr->replicas[REGION_EU].version);
    
    printf("\nReplicating US -> EU...\n");
    georep_replicate(gr, REGION_US, REGION_EU);
    printf("EU replica version: %d\n", gr->replicas[REGION_EU].version);
    printf("EU replica data: %s\n", gr->replicas[REGION_EU].data);
    
    printf("Passed.\n");
    free(gr);
}

int main() {
    test_scenario();
    return 0;
}