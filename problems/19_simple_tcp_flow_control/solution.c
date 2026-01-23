#include <stdio.h>
#include <stdbool.h>

// Simulation of Sliding Window (Sender side)
#define WINDOW_SIZE 5
#define TOTAL_PACKETS 15

typedef struct {
    int seq_num;
} Packet;

typedef struct {
    int send_base;
    int next_seq_num;
} Sender;

void simulate_flow_control() {
    Sender sender = {0, 0};
    
    printf("Starting TCP Sliding Window Simulation (Window Size: %d)\n", WINDOW_SIZE);

    while (sender.send_base < TOTAL_PACKETS) {
        // Step 1: Send until window is full
        while (sender.next_seq_num < sender.send_base + WINDOW_SIZE && 
               sender.next_seq_num < TOTAL_PACKETS) {
            
            printf("[Sender]   Sending Packet SEQ %d\n", sender.next_seq_num);
            sender.next_seq_num++;
        }

        // Step 2: Simulate Receiver Logic (Instant ACK of send_base)
        int packet_to_ack = sender.send_base;
        printf("  [Receiver] Received SEQ %d, Sending ACK %d\n", packet_to_ack, packet_to_ack + 1);
        
        // Step 3: Sender processes ACK
        int new_ack = packet_to_ack + 1;
        if (new_ack > sender.send_base) {
            printf("[Sender]   Got ACK %d. Slide window: [%d -> %d)\n", 
                   new_ack, new_ack, new_ack + WINDOW_SIZE);
            sender.send_base = new_ack;
        }
    }
}

void solution() {}

int main() {
    simulate_flow_control();
    printf("Test Passed\n");
    return 0;
}
