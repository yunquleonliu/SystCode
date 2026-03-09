/**
 * Problem 58: PCIe Enumeration
 * PCI Express device discovery and enumeration.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint16_t vendor_id;
    uint16_t device_id;
    uint8_t class_code;
    uint8_t subclass;
    int is_valid;
} PCIeDevice;

typedef struct {
    PCIeDevice devices[256];
    int device_count;
} PCIeBus;

PCIeBus* pcie_init() {
    PCIeBus* bus = calloc(1, sizeof(PCIeBus));
    printf("PCIe bus initialized\n");
    return bus;
}

void pcie_scan(PCIeBus* bus) {
    printf("Scanning PCIe bus...\n");
    // Simulate device discovery
    bus->devices[0].vendor_id = 0x8086;  // Intel
    bus->devices[0].device_id = 0x0d04;
    bus->devices[0].is_valid = 1;
    bus->device_count = 1;
    
    printf("  Found device: vendor=0x%04x, device=0x%04x\n",
           bus->devices[0].vendor_id, bus->devices[0].device_id);
}

void pcie_enumerate(PCIeBus* bus) {
    printf("\nEnumerating %d devices:\n", bus->device_count);
    for (int i = 0; i < bus->device_count; i++) {
        if (bus->devices[i].is_valid) {
            printf("  Device %d: vendor=0x%04x\n", i, bus->devices[i].vendor_id);
        }
    }
}

int main() {
    printf("=== PCIe Enumeration ===\n\n");
    PCIeBus* bus = pcie_init();
    pcie_scan(bus);
    pcie_enumerate(bus);
    free(bus);
    return 0;
}