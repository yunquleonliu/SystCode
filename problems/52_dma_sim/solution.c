/**
 * Problem 52: DMA (Direct Memory Access) Simulation
 * Memory transfer without CPU involvement.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t src;
    uint64_t dst;
    uint32_t length;
    int status;
} DMARequest;

typedef struct {
    DMARequest* queue;
    int queue_size;
    int tail;
    uint8_t* memory;
} DMAController;

DMAController* dma_init() {
    DMAController* dma = calloc(1, sizeof(DMAController));
    dma->queue_size = 16;
    dma->queue = calloc(16, sizeof(DMARequest));
    dma->memory = calloc(1, 1024 * 1024);
    printf("DMA controller initialized\n");
    return dma;
}

void dma_request(DMAController* dma, uint64_t src, uint64_t dst, uint32_t len) {
    DMARequest* req = &dma->queue[dma->tail++];
    req->src = src;
    req->dst = dst;
    req->length = len;
    printf("DMA request: 0x%llx -> 0x%llx (%u bytes)\n", 
           (unsigned long long)src, (unsigned long long)dst, len);
}

void dma_process(DMAController* dma) {
    for (int i = 0; i < dma->tail; i++) {
        DMARequest* req = &dma->queue[i];
        memcpy(dma->memory + req->dst, dma->memory + req->src, req->length);
        req->status = 1;  // Complete
        printf("  Completed %u bytes\n", req->length);
    }
    dma->tail = 0;
}

int main() {
    printf("=== DMA Simulation ===\n\n");
    DMAController* dma = dma_init();
    dma_request(dma, 0, 0x1000, 4096);
    dma_request(dma, 0x1000, 0x2000, 4096);
    dma_process(dma);
    free(dma->memory);
    free(dma->queue);
    free(dma);
    return 0;
}