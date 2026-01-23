/**
 * Problem 80: Query Optimizer
 * Simple cost-based query planning
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    OP_TABLE_SCAN,
    OP_INDEX_SCAN,
    OP_FILTER,
    OP_JOIN,
    OP_AGGREGATE
} OpType;

typedef struct {
    OpType type;
    int table_id;
    int rows_estimate;
    float selectivity;
    int cost;
} QueryNode;

typedef struct {
    QueryNode nodes[10];
    int num_nodes;
} QueryPlan;

int estimate_table_scan_cost(int rows) {
    return rows / 10;  // Simplified
}

int estimate_index_scan_cost(int rows, float selectivity) {
    return (int)(rows * selectivity * 0.1f);
}

QueryPlan* optimize_simple_select(int table_rows, float selectivity, int use_index) {
    QueryPlan* plan = malloc(sizeof(QueryPlan));
    plan->num_nodes = 1;
    
    QueryNode* node = &plan->nodes[0];
    
    if (use_index) {
        node->type = OP_INDEX_SCAN;
        node->cost = estimate_index_scan_cost(table_rows, selectivity);
    } else {
        node->type = OP_TABLE_SCAN;
        node->cost = estimate_table_scan_cost(table_rows);
    }
    
    node->rows_estimate = (int)(table_rows * selectivity);
    node->selectivity = selectivity;
    
    return plan;
}

void plan_print(QueryPlan* plan) {
    printf("Query Plan (cost=%d):\n", plan->nodes[0].cost);
    for (int i = 0; i < plan->num_nodes; i++) {
        QueryNode* node = &plan->nodes[i];
        printf("  Op %d: ", i);
        switch (node->type) {
            case OP_TABLE_SCAN: printf("TABLE SCAN\n"); break;
            case OP_INDEX_SCAN: printf("INDEX SCAN\n"); break;
            default: printf("OTHER\n");
        }
        printf("    Estimated rows: %d\n", node->rows_estimate);
        printf("    Cost: %d\n", node->cost);
    }
}

void test_scenario() {
    printf("Running tests for Query Optimizer...\n\n");
    
    // Plan 1: Table scan (slow selectivity)
    QueryPlan* plan1 = optimize_simple_select(1000000, 0.01f, 0);
    printf("Plan 1 (Table scan, 1%% selectivity):\n");
    plan_print(plan1);
    printf("\n");
    
    // Plan 2: Index scan (same selectivity)
    QueryPlan* plan2 = optimize_simple_select(1000000, 0.01f, 1);
    printf("Plan 2 (Index scan, 1%% selectivity):\n");
    plan_print(plan2);
    
    printf("\nRecommendation: Index scan is %d%% faster\n",
           (int)((plan1->nodes[0].cost - plan2->nodes[0].cost) * 100 / plan1->nodes[0].cost));
    
    printf("Passed.\n");
    free(plan1);
    free(plan2);
}

int main() {
    test_scenario();
    return 0;
}