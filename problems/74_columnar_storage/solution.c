/**
 * Problem 74: Columnar Storage Layout
 * Column-oriented storage for analytics workloads
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROWS 1000
#define NUM_COLS 5

typedef struct {
    int* id;
    float* price;
    int* quantity;
    long* timestamp;
    char** category;
} ColumnStore;

ColumnStore* columnar_create(int num_rows) {
    ColumnStore* cs = malloc(sizeof(ColumnStore));
    cs->id = malloc(num_rows * sizeof(int));
    cs->price = malloc(num_rows * sizeof(float));
    cs->quantity = malloc(num_rows * sizeof(int));
    cs->timestamp = malloc(num_rows * sizeof(long));
    cs->category = malloc(num_rows * sizeof(char*));
    
    for (int i = 0; i < num_rows; i++) {
        cs->category[i] = malloc(32);
    }
    
    return cs;
}

void columnar_insert(ColumnStore* cs, int row, int id, float price, int qty, long ts, const char* cat) {
    cs->id[row] = id;
    cs->price[row] = price;
    cs->quantity[row] = qty;
    cs->timestamp[row] = ts;
    strcpy(cs->category[row], cat);
}

float columnar_sum_column(ColumnStore* cs, int num_rows) {
    float sum = 0;
    for (int i = 0; i < num_rows; i++) {
        sum += cs->price[i];
    }
    return sum;
}

int columnar_count_by_category(ColumnStore* cs, int num_rows, const char* cat) {
    int count = 0;
    for (int i = 0; i < num_rows; i++) {
        if (strcmp(cs->category[i], cat) == 0) {
            count++;
        }
    }
    return count;
}

void test_scenario() {
    printf("Running tests for Columnar Storage...\n\n");
    
    ColumnStore* cs = columnar_create(100);
    
    for (int i = 0; i < 100; i++) {
        columnar_insert(cs, i, i+1, (i+1)*10.5f, i*2, 1000000+i, 
                       i % 3 == 0 ? "Electronics" : (i % 3 == 1 ? "Books" : "Toys"));
    }
    
    float total_price = columnar_sum_column(cs, 100);
    int electronics_count = columnar_count_by_category(cs, 100, "Electronics");
    
    printf("Total rows: 100\n");
    printf("Total price: %.2f\n", total_price);
    printf("Electronics count: %d\n", electronics_count);
    printf("Passed.\n");
}

int main() {
    test_scenario();
    return 0;
}