/**
 * Problem 24: Gossip Protocol
 * Epidemic-style information dissemination.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NODES 10
#define MAX_MESSAGES 100

typedef struct {
    int id;
    char data[64];
    int version;
} Message;

typedef struct {
    int node_id;
    Message messages[MAX_MESSAGES];
    int message_count;
    bool alive;
} GossipNode;

typedef struct {
    GossipNode nodes[MAX_NODES];
    int node_count;
    int fanout;  // Number of nodes to gossip to each round
} GossipCluster;

void cluster_init(GossipCluster* c, int num_nodes, int fanout) {
    c->node_count = num_nodes;
    c->fanout = fanout;
    for (int i = 0; i < num_nodes; i++) {
        c->nodes[i].node_id = i;
        c->nodes[i].message_count = 0;
        c->nodes[i].alive = true;
    }
}

void node_add_message(GossipNode* node, int id, const char* data, int version) {
    // Check if we already have this message
    for (int i = 0; i < node->message_count; i++) {
        if (node->messages[i].id == id) {
            if (node->messages[i].version < version) {
                node->messages[i].version = version;
                strncpy(node->messages[i].data, data, 63);
            }
            return;
        }
    }
    // New message
    if (node->message_count < MAX_MESSAGES) {
        Message* m = &node->messages[node->message_count++];
        m->id = id;
        m->version = version;
        strncpy(m->data, data, 63);
    }
}

void gossip_round(GossipCluster* c, int source_id) {
    GossipNode* source = &c->nodes[source_id];
    
    printf("Node %d gossiping to %d peers...\n", source_id, c->fanout);
    
    // Select random peers
    for (int i = 0; i < c->fanout && i < c->node_count - 1; i++) {
        int target_id;
        do {
            target_id = rand() % c->node_count;
        } while (target_id == source_id);
        
        GossipNode* target = &c->nodes[target_id];
        if (!target->alive) continue;
        
        // Share all messages
        for (int j = 0; j < source->message_count; j++) {
            Message* m = &source->messages[j];
            node_add_message(target, m->id, m->data, m->version);
        }
        printf("  -> Sent to Node %d\n", target_id);
    }
}

void print_cluster_state(GossipCluster* c) {
    printf("\nCluster State:\n");
    for (int i = 0; i < c->node_count; i++) {
        GossipNode* n = &c->nodes[i];
        printf("  Node %d: %d messages\n", n->node_id, n->message_count);
    }
}

int main() {
    printf("=== Gossip Protocol ===\n\n");
    srand(time(NULL));
    
    GossipCluster cluster;
    cluster_init(&cluster, 5, 2);
    
    // Node 0 has initial data
    node_add_message(&cluster.nodes[0], 1, "Hello World", 1);
    node_add_message(&cluster.nodes[0], 2, "Config Update", 1);
    
    printf("Initial state:\n");
    print_cluster_state(&cluster);
    
    // Run gossip rounds
    for (int round = 0; round < 3; round++) {
        printf("\n--- Round %d ---\n", round + 1);
        for (int i = 0; i < cluster.node_count; i++) {
            if (cluster.nodes[i].message_count > 0) {
                gossip_round(&cluster, i);
            }
        }
    }
    
    printf("\nFinal state:");
    print_cluster_state(&cluster);
    
    return 0;
}