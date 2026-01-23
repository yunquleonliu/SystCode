/**
 * Problem 71: B+ Tree Index
 * Self-balancing tree optimized for disk I/O and range queries
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define B_TREE_ORDER 5
#define MAX_KEYS (2 * B_TREE_ORDER - 1)

typedef struct BNode {
    int keys[MAX_KEYS];
    struct BNode* children[2 * B_TREE_ORDER];
    int num_keys;
    int is_leaf;
} BNode;

typedef struct {
    BNode* root;
    int height;
} BPlusTree;

BPlusTree* btree_create() {
    BPlusTree* tree = malloc(sizeof(BPlusTree));
    tree->root = malloc(sizeof(BNode));
    tree->root->num_keys = 0;
    tree->root->is_leaf = 1;
    tree->height = 0;
    return tree;
}

void btree_insert_leaf(BNode* leaf, int key) {
    int i = leaf->num_keys - 1;
    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    leaf->keys[i + 1] = key;
    leaf->num_keys++;
}

void btree_insert(BPlusTree* tree, int key) {
    if (tree->root->num_keys >= MAX_KEYS) {
        BNode* new_root = malloc(sizeof(BNode));
        new_root->is_leaf = 0;
        new_root->num_keys = 0;
        new_root->children[0] = tree->root;
        tree->root = new_root;
        tree->height++;
    }
    
    BNode* curr = tree->root;
    while (!curr->is_leaf) {
        int i = 0;
        while (i < curr->num_keys && key > curr->keys[i]) {
            i++;
        }
        curr = curr->children[i];
    }
    
    btree_insert_leaf(curr, key);
}

int btree_search(BPlusTree* tree, int key) {
    BNode* curr = tree->root;
    
    while (curr != NULL) {
        int i = 0;
        while (i < curr->num_keys && key > curr->keys[i]) {
            i++;
        }
        
        if (i < curr->num_keys && key == curr->keys[i]) {
            return 1;  // Found
        }
        
        if (curr->is_leaf) {
            return 0;  // Not found
        }
        
        curr = curr->children[i];
    }
    
    return 0;
}

void test_scenario() {
    printf("Running tests for B+ Tree Index...\n\n");
    
    BPlusTree* tree = btree_create();
    
    // Insert values
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++) {
        btree_insert(tree, values[i]);
    }
    
    printf("Inserted %d values\n", 8);
    printf("Tree height: %d\n", tree->height);
    
    // Search
    assert(btree_search(tree, 10) == 1);
    assert(btree_search(tree, 6) == 1);
    assert(btree_search(tree, 99) == 0);
    
    printf("Search tests passed\n");
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}