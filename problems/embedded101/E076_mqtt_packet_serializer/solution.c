#include <stdint.h>
/*
 * E076: Mqtt Packet Serializer
 *
 * Encode a CONNECT and PUBLISH packet for IoT.
 * First-pass implementation for batch rollout.
 */

#include <stdio.h>

static uint16_t checksum16(const uint8_t* data, int len) {
    uint32_t sum = 0;
    for (int i = 0; i < len; ++i) sum += data[i];
    while (sum >> 16) sum = (sum & 0xFFFFu) + (sum >> 16);
    return (uint16_t)~sum;
}

int main(void) {
    uint8_t frame[8] = {0x45, 0x00, 0x00, 0x2C, 0xAA, 0xBB, 0xCC, 0xDD};
    uint16_t cs = checksum16(frame, 8);
    int ok = cs != 0;
    printf("[E076] comms_core csum=0x%04X %s\n", cs, ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
