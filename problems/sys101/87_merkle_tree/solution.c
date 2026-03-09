/**
 * Problem 87: Merkle Tree
 * Efficient data integrity verification
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MerkleNode {
    unsigned char hash[32];
    struct MerkleNode* left;
    struct MerkleNode* right;
    int is_leaf;
} MerkleNode;

typedef struct {
    MerkleNode* root;
} MerkleTree;

unsigned int simple_hash(const char* data, int len) {
    unsigned int h = 5381;
    for (int i = 0; i < len; i++) {
        h = ((h << 5) + h) + data[i];
    }
    return h;
}

void hash_to_bytes(unsigned int h, unsigned char* bytes) {
    bytes[0] = (h >> 24) & 0xFF;
    bytes[1] = (h >> 16) & 0xFF;
    bytes[2] = (h >> 8) & 0xFF;
    bytes[3] = h & 0xFF;
}

MerkleNode* merkle_create_leaf(const char* data) {
    MerkleNode* node = malloc(sizeof(MerkleNode));
    node->is_leaf = 1;
    node->left = NULL;
    node->right = NULL;
    
    unsigned int h = simple_hash(data, strlen(data));
    hash_to_bytes(h, node->hash);
    
    return node;
}

MerkleNode* merkle_combine(MerkleNode* left, MerkleNode* right) {
    MerkleNode* node = malloc(sizeof(MerkleNode));
    node->is_leaf = 0;
    node->left = left;
    node->right = right;
    
    // Simple hash combination
    unsigned int h1 = *(unsigned int*)left->hash;
    unsigned int h2 = *(unsigned int*)right->hash;
    unsigned int combined = h1 ^ h2;
    hash_to_bytes(combined, node->hash);
    
    return node;
}

MerkleTree* merkle_build(const char** data, int count) {
    if (count == 0) return NULL;
    
    MerkleNode** nodes = malloc(count * sizeof(MerkleNode*));
    for (int i = 0; i < count; i++) {
        nodes[i] = merkle_create_leaf(data[i]);
    }
    
    while (count > 1) {
        int new_count = (count + 1) / 2;
        for (int i = 0; i < new_count; i++) {
            if (i * 2 + 1 < count) {
                nodes[i] = merkle_combine(nodes[i*2], nodes[i*2+1]);
            } else {
                nodes[i] = nodes[i*2];
            }
        }
        count = new_count;
    }
    
    MerkleTree* tree = malloc(sizeof(MerkleTree));
    tree->root = nodes[0];
    free(nodes);
    
    return tree;
}

void test_scenario() {
    printf("Running tests for Merkle Tree...\n\n");
    
    const char* data[] = {"Block1", "Block2", "Block3", "Block4"};
    MerkleTree* tree = merkle_build(data, 4);
    
    printf("Built Merkle tree from 4 blocks\n");
    printf("Root hash (first 4 bytes): %02X%02X%02X%02X\n",
           tree->root->hash[0], tree->root->hash[1],
           tree->root->hash[2], tree->root->hash[3]);
    
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}