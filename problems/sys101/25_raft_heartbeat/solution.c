/**
 * Problem 25: Raft Heartbeat & Leader Election
 * Consensus protocol with leader election.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum { FOLLOWER, CANDIDATE, LEADER } NodeState;

typedef struct {
    int id;
    NodeState state;
    int current_term;
    int voted_for;  // -1 if none
    int votes_received;
    int election_timeout;
    int heartbeat_interval;
} RaftNode;

typedef struct {
    RaftNode* nodes;
    int node_count;
    int current_leader;
} RaftCluster;

void node_init(RaftNode* node, int id) {
    node->id = id;
    node->state = FOLLOWER;
    node->current_term = 0;
    node->voted_for = -1;
    node->votes_received = 0;
    node->election_timeout = 150 + (rand() % 150);  // 150-300ms
    node->heartbeat_interval = 50;
}

void cluster_init(RaftCluster* c, int num_nodes) {
    c->node_count = num_nodes;
    c->nodes = malloc(sizeof(RaftNode) * num_nodes);
    c->current_leader = -1;
    for (int i = 0; i < num_nodes; i++) {
        node_init(&c->nodes[i], i);
    }
}

// Request vote RPC
bool request_vote(RaftNode* voter, int candidate_id, int candidate_term) {
    if (candidate_term > voter->current_term) {
        voter->current_term = candidate_term;
        voter->voted_for = -1;
        voter->state = FOLLOWER;
    }
    
    if (candidate_term >= voter->current_term && 
        (voter->voted_for == -1 || voter->voted_for == candidate_id)) {
        voter->voted_for = candidate_id;
        printf("  Node %d: Voting for Node %d (term %d)\n", voter->id, candidate_id, candidate_term);
        return true;
    }
    return false;
}

void start_election(RaftCluster* c, int node_id) {
    RaftNode* candidate = &c->nodes[node_id];
    candidate->state = CANDIDATE;
    candidate->current_term++;
    candidate->voted_for = node_id;
    candidate->votes_received = 1;  // Vote for self
    
    printf("Node %d: Starting election (term %d)\n", node_id, candidate->current_term);
    
    // Request votes from all other nodes
    for (int i = 0; i < c->node_count; i++) {
        if (i != node_id) {
            if (request_vote(&c->nodes[i], node_id, candidate->current_term)) {
                candidate->votes_received++;
            }
        }
    }
    
    // Check if won majority
    if (candidate->votes_received > c->node_count / 2) {
        candidate->state = LEADER;
        c->current_leader = node_id;
        printf("Node %d: Became LEADER with %d votes\n", node_id, candidate->votes_received);
    }
}

void send_heartbeat(RaftCluster* c) {
    if (c->current_leader < 0) return;
    
    RaftNode* leader = &c->nodes[c->current_leader];
    printf("Leader %d: Sending heartbeat (term %d)\n", leader->id, leader->current_term);
    
    for (int i = 0; i < c->node_count; i++) {
        if (i != c->current_leader) {
            RaftNode* follower = &c->nodes[i];
            if (leader->current_term >= follower->current_term) {
                follower->current_term = leader->current_term;
                follower->state = FOLLOWER;
            }
        }
    }
}

void cluster_free(RaftCluster* c) {
    free(c->nodes);
}

int main() {
    printf("=== Raft Leader Election ===\n\n");
    srand(time(NULL));
    
    RaftCluster cluster;
    cluster_init(&cluster, 5);
    
    // Simulate election timeout on node 0
    printf("--- Election starts ---\n");
    start_election(&cluster, 0);
    
    printf("\n--- Heartbeat phase ---\n");
    for (int i = 0; i < 3; i++) {
        send_heartbeat(&cluster);
    }
    
    cluster_free(&cluster);
    return 0;
}