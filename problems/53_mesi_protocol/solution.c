/**
 * Problem 53: MESI Cache Coherency Protocol
 * Multi-core cache coherency.
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INVALID, SHARED, EXCLUSIVE, MODIFIED
} CacheState;

typedef struct {
    uint64_t addr;
    CacheState state;
    uint8_t data[64];
} CacheLine;

typedef struct {
    int cpu_id;
    CacheLine lines[256];
    int line_count;
} Cache;

Cache* cache_create(int cpu_id) {
    Cache* cache = calloc(1, sizeof(Cache));
    cache->cpu_id = cpu_id;
    printf("Cache %d initialized\n", cpu_id);
    return cache;
}

void cache_load(Cache* cache, uint64_t addr) {
    CacheLine* line = &cache->lines[cache->line_count];
    line->addr = addr;
    line->state = EXCLUSIVE;
    printf("CPU %d: LOAD 0x%llx (state=EXCLUSIVE)\n", 
           cache->cpu_id, (unsigned long long)addr);
    cache->line_count++;
}

void cache_store(Cache* cache, uint64_t addr) {
    for (int i = 0; i < cache->line_count; i++) {
        if (cache->lines[i].addr == addr) {
            cache->lines[i].state = MODIFIED;
            printf("CPU %d: STORE 0x%llx (state=MODIFIED)\n", 
                   cache->cpu_id, (unsigned long long)addr);
            return;
        }
    }
}

int main() {
    printf("=== MESI Protocol ===\n\n");
    Cache* c0 = cache_create(0);
    Cache* c1 = cache_create(1);
    
    cache_load(c0, 0x1000);
    cache_store(c0, 0x1000);
    
    free(c0);
    free(c1);
    return 0;
}