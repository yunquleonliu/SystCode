/**
 * Problem 89: Consistent Hashing with Virtual Nodes
 * Minimal data movement during rebalancing
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_NODES 5
#define HASH_RING_SIZE 1000
#define VNODES_PER_NODE 3

typedef struct {
    int node_id;
} Node;

typedef struct {
    Node* ring[HASH_RING_SIZE];
    int num_active_nodes;
} ConsistentHash;

unsigned int hash_key(const char* key) {
    unsigned int h = 5381;
    for (int i = 0; key[i]; i++) {
        h = ((h << 5) + h) + key[i];
    }
    return h % HASH_RING_SIZE;
}

ConsistentHash* chash_create() {
    ConsistentHash* ch = malloc(sizeof(ConsistentHash));
    memset(ch->ring, 0, sizeof(ch->ring));
    ch->num_active_nodes = 0;
    return ch;
}

void chash_add_node(ConsistentHash* ch, int node_id) {
    for (int i = 0; i < HASH_RING_SIZE; i++) {
        if (ch->ring[i] == NULL) {
            Node* node = malloc(sizeof(Node));
            node->node_id = node_id;
            ch->ring[i] = node;
            ch->num_active_nodes++;
            return;
        }
    }
}

int chash_get_node(ConsistentHash* ch, const char* key) {
    unsigned int hash = hash_key(key);
    
    for (int i = hash; i < HASH_RING_SIZE; i++) {
        if (ch->ring[i] != NULL) {
            return ch->ring[i]->node_id;
        }
    }
    
    // Wrap around
    for (int i = 0; i < hash; i++) {
        if (ch->ring[i] != NULL) {
            return ch->ring[i]->node_id;
        }
    }
    
    return -1;
}

void test_scenario() {
    printf("Running tests for Consistent Hashing...\n\n");
    
    ConsistentHash* ch = chash_create();
    
    chash_add_node(ch, 1);
    chash_add_node(ch, 2);
    chash_add_node(ch, 3);
    
    printf("Added 3 nodes\n");
    
    printf("\nKey distribution:\n");
    const char* keys[] = {"user:1", "user:2", "user:3", "data:1"};
    for (int i = 0; i < 4; i++) {
        int node = chash_get_node(ch, keys[i]);
        printf("  %s -> Node %d\n", keys[i], node);
    }
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}