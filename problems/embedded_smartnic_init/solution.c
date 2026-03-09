#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// --- Simulated Hardware Registers -----------------------------------------
#define BAR0_SIZE 4096
#define REG_DEVICE_STATUS 0x00
#define REG_FW_VERSION    0x04
#define REG_ADMIN_Q_BASE  0x08  // Physical Address of Admin Queue (High/Low)
#define REG_ADMIN_Q_SIZE  0x10  // Number of entries
#define REG_ADMIN_DB      0x14  // Doorbell (Tail Pointer)
#define REG_INT_MASK      0x18  // Interrupt Mask

// Status Bits
#define STS_RESETTING     (1<<0)
#define STS_READY         (1<<1)

static uint8_t g_bar0[BAR0_SIZE];

// Mock hardware access
uint32_t pci_read_32(uint32_t offset) {
    if (offset >= BAR0_SIZE) return 0xFFFFFFFF;
    return *(uint32_t*)(g_bar0 + offset);
}

void pci_write_32(uint32_t offset, uint32_t val) {
    if (offset >= BAR0_SIZE) return;
    *(uint32_t*)(g_bar0 + offset) = val;
    // Simulate HW side effect:
    if (offset == REG_ADMIN_DB) {
        printf("[SimHW] Doorbell Ring! New Tail: %d\n", val);
        // In real hardware, this would trigger processing.
    }
}

// --- Driver Data Structures -----------------------------------------------

// Admin Command Entry (64 bytes)
typedef struct {
    uint8_t opcode;
    uint8_t flags;
    uint16_t command_id;
    uint32_t rsvd;
    uint64_t parameter1;
    uint64_t parameter2;
    uint64_t buffer_phys_addr;
    uint32_t buffer_len;
    uint8_t padding[28];
} AdminCmd;

// Admin Completion Entry (16 bytes)
typedef struct {
    uint8_t status;
    uint8_t command_specific;
    uint16_t command_id;
    uint16_t sq_head_ptr;
    uint16_t sq_id;
    uint32_t result;
    uint32_t rsvd;
} AdminCpl;

// Host Queue State
typedef struct {
    AdminCmd* cmd_ring;   // Virtual Address (matches phys for simulation)
    AdminCpl* cpl_ring;   // Virtual Address (matches phys for simulation)
    uint32_t size;        // Number of entries
    uint32_t head;        // Consumer (HW) Index
    uint32_t tail;        // Producer (SW) Index
    uint16_t phase;       // Completion status phase bit
} AdminQueue;

// --- Implement This Function ----------------------------------------------

/* 
   TODO: Initialize the Admin Queue 
   1. Allocate host memory for the rings.
   2. Write the base address to the device registers (REG_ADMIN_Q_BASE).
   3. Tell the device the queue size (REG_ADMIN_Q_SIZE).
   4. Clear the doorbell register to 0.
*/
void nic_admin_queue_init(AdminQueue* q, uint32_t entries) {
    // Allocation simulation
    q->cmd_ring = calloc(entries, sizeof(AdminCmd));
    q->cpl_ring = calloc(entries, sizeof(AdminCpl));
    q->size = entries;
    q->head = 0;
    q->tail = 0;
    q->phase = 1;

    // TODO: Write registers...
    // pci_write_32(REG_ADMIN_Q_BASE, (uint32_t)(uintptr_t)q->cmd_ring); 
    // ...
    printf("[Driver] Initialized Admin Queue with %d entries.\n", entries);
}

/* 
   TODO: Post a command to the Admin Queue 
   1. Get the next free slot at `q->tail`.
   2. Fill in the Opcode and Command ID.
   3. Increment `q->tail` (Wrap around if needed).
   4. Ring the Doorbell (Write generic register REG_ADMIN_DB).
*/
int nic_admin_cmd_submit(AdminQueue* q, uint8_t opcode, uint64_t param) {
    // Ensure queue has space...
    
    // Fill command...
    AdminCmd* cmd = &q->cmd_ring[q->tail];
    // cmd->opcode = opcode;
    // ...

    // Update Tail...
    
    // Ring Doorbell (Memory Barrier needed in real HW)...
    // pci_write_32(REG_ADMIN_DB, q->tail);
    
    return 0; // Success
}

/* 
   TODO: Poll for Completion 
   1. Check the `status` phase bit of the entry at `q->head`.
   2. If phase bit flipped, the command is done.
   3. Increment `q->head`.
*/
int nic_poll_completion(AdminQueue* q) {
    // Check completion ring...
    return -1; // Busy
}


// --- Test Harness ---------------------------------------------------------

// Simulate Firmware processing the command in the background
void sim_fw_process_admin_cmd(AdminQueue* q) {
    // Assume q->tail was updated by driver
    if (q->head == q->tail) return; // Nothing to do

    // Process command at head...
    printf("[SimFW] Processing command %d...\n", q->head);
    
    // Write completion...
    q->cpl_ring[q->head].status = 1; // Success
    q->cpl_ring[q->head].result = 0xCAFEBABE; // Return value
    
    // Advance simulation head (HW consumes command)
    q->head = (q->head + 1) % q->size;
}

int main() {
    printf("Starting SmartNIC Initialization Lab...\n");

    // 1. Reset Device
    *(uint32_t*)(g_bar0 + REG_DEVICE_STATUS) = STS_READY; // Simulate Ready state
    
    uint32_t status = pci_read_32(REG_DEVICE_STATUS);
    if (!(status & STS_READY)) {
        printf("Error: Device not ready!\n");
        return -1;
    }
    printf("Device Status: READY\n");

    // 2. Initialize Logic
    AdminQueue aq;
    nic_admin_queue_init(&aq, 16);

    // 3. Send INIT command (Opcode 0x01)
    nic_admin_cmd_submit(&aq, 0x01, 0xDEADBEEF);

    // 4. Simulate Firmware Response
    sim_fw_process_admin_cmd(&aq);

    // 5. Poll for completion
    int res = nic_poll_completion(&aq);
    
    if (res == 0) {
        printf("Success: Command Completed!\n");
    } else {
        printf("Waiting for completion...\n");
    }

    return 0;
}
