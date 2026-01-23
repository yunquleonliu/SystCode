/**
 * Problem 22: Consistent Hashing
 * Distribute keys across nodes with minimal remapping on changes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define RING_SIZE 360
#define MAX_NODES 10
#define VIRTUAL_NODES 3

typedef struct {
    char name[32];
    uint32_t positions[VIRTUAL_NODES];
} Node;

typedef struct {
    Node nodes[MAX_NODES];
    int node_count;
} HashRing;

// Simple hash function
uint32_t hash(const char* key) {
    uint32_t h = 5381;
    while (*key) {
        h = ((h << 5) + h) + *key++;
    }
    return h % RING_SIZE;
}

void ring_init(HashRing* ring) {
    ring->node_count = 0;
}

void ring_add_node(HashRing* ring, const char* name) {
    if (ring->node_count >= MAX_NODES) return;
    
    Node* n = &ring->nodes[ring->node_count];
    strncpy(n->name, name, 31);
    
    // Create virtual nodes
    for (int i = 0; i < VIRTUAL_NODES; i++) {
        char vnode_key[64];
        snprintf(vnode_key, sizeof(vnode_key), "%s#%d", name, i);
        n->positions[i] = hash(vnode_key);
        printf("Added virtual node %s at position %u\n", vnode_key, n->positions[i]);
    }
    
    ring->node_count++;
}

const char* ring_get_node(HashRing* ring, const char* key) {
    if (ring->node_count == 0) return NULL;
    
    uint32_t key_hash = hash(key);
    
    // Find first node position >= key_hash
    uint32_t min_dist = RING_SIZE;
    const char* closest = ring->nodes[0].name;
    
    for (int i = 0; i < ring->node_count; i++) {
        for (int j = 0; j < VIRTUAL_NODES; j++) {
            uint32_t pos = ring->nodes[i].positions[j];
            uint32_t dist = (pos >= key_hash) ? (pos - key_hash) : (RING_SIZE - key_hash + pos);
            if (dist < min_dist) {
                min_dist = dist;
                closest = ring->nodes[i].name;
            }
        }
    }
    
    return closest;
}

int main() {
    printf("=== Consistent Hashing ===\n\n");
    
    HashRing ring;
    ring_init(&ring);
    
    ring_add_node(&ring, "NodeA");
    ring_add_node(&ring, "NodeB");
    ring_add_node(&ring, "NodeC");
    
    printf("\nKey routing:\n");
    const char* keys[] = {"user:1", "user:2", "user:3", "session:abc", "data:xyz"};
    for (int i = 0; i < 5; i++) {
        printf("  %s -> %s (hash=%u)\n", keys[i], ring_get_node(&ring, keys[i]), hash(keys[i]));
    }
    
    return 0;
}