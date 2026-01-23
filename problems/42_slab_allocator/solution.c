/**
 * Problem 42: Slab Allocator
 * Object caching allocator for fixed-size objects.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SLAB_SIZE 4096

typedef struct {
    void* memory;
    int obj_size;
    int capacity;
    int free_count;
    void** freelist;
} Slab;

typedef struct {
    int obj_size;
    Slab* slabs;
    int num_slabs;
    const char* name;
} SlabCache;

Slab* slab_create(int obj_size) {
    Slab* slab = malloc(sizeof(Slab));
    slab->memory = malloc(SLAB_SIZE);
    slab->obj_size = obj_size;
    slab->capacity = SLAB_SIZE / obj_size;
    slab->free_count = slab->capacity;
    slab->freelist = malloc(sizeof(void*) * slab->capacity);
    for (int i = 0; i < slab->capacity; i++) {
        slab->freelist[i] = (char*)slab->memory + i * obj_size;
    }
    return slab;
}

SlabCache* slab_cache_create(const char* name, int obj_size) {
    SlabCache* cache = calloc(1, sizeof(SlabCache));
    cache->name = name;
    cache->obj_size = obj_size;
    cache->slabs = slab_create(obj_size);
    cache->num_slabs = 1;
    printf("Cache '%s' created (obj_size=%d, objs/slab=%d)\n", 
           name, obj_size, cache->slabs->capacity);
    return cache;
}

void* slab_alloc(SlabCache* cache) {
    if (cache->slabs->free_count == 0) {
        Slab* new_slab = slab_create(cache->obj_size);
        new_slab->freelist = cache->slabs->freelist + 1;
        free(cache->slabs);
        cache->slabs = new_slab;
        cache->num_slabs++;
    }
    void* obj = cache->slabs->freelist[--cache->slabs->free_count];
    memset(obj, 0, cache->obj_size);
    return obj;
}

void slab_free(SlabCache* cache, void* obj) {
    cache->slabs->freelist[cache->slabs->free_count++] = obj;
}

void slab_cache_destroy(SlabCache* cache) {
    free(cache->slabs->memory);
    free(cache->slabs->freelist);
    free(cache->slabs);
    free(cache);
}

int main() {
    printf("=== Slab Allocator ===\n\n");
    SlabCache* cache = slab_cache_create("test_obj", 64);
    void* obj1 = slab_alloc(cache);
    void* obj2 = slab_alloc(cache);
    printf("Allocated 2 objects\n");
    slab_free(cache, obj1);
    printf("Freed object 1\n");
    slab_cache_destroy(cache);
    return 0;
}