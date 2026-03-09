/**
 * Problem 51: VirtIO Driver
 * Virtual I/O device interface.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t device_id;
    uint32_t vendor_id;
} VirtIOHeader;

typedef struct {
    VirtIOHeader header;
    void** queue;
    int queue_size;
    int queue_pos;
} VirtIODevice;

VirtIODevice* virtio_init(int device_id) {
    VirtIODevice* dev = calloc(1, sizeof(VirtIODevice));
    dev->header.magic = 0x74726976;  // "virt"
    dev->header.version = 1;
    dev->header.device_id = device_id;
    dev->header.vendor_id = 0x1af4;
    dev->queue_size = 256;
    dev->queue = calloc(256, sizeof(void*));
    printf("VirtIO device initialized (ID=%d)\n", device_id);
    return dev;
}

void virtio_queue_add(VirtIODevice* dev, void* buffer) {
    if (dev->queue_pos < dev->queue_size) {
        dev->queue[dev->queue_pos++] = buffer;
        printf("  Queued buffer (pos=%d)\n", dev->queue_pos - 1);
    }
}

void virtio_kick(VirtIODevice* dev) {
    printf("Kicked %d buffers\n", dev->queue_pos);
    dev->queue_pos = 0;
}

int main() {
    printf("=== VirtIO Driver ===\n\n");
    VirtIODevice* dev = virtio_init(1);  // Network device
    virtio_queue_add(dev, (void*)0x1000);
    virtio_queue_add(dev, (void*)0x2000);
    virtio_kick(dev);
    free(dev->queue);
    free(dev);
    return 0;
}