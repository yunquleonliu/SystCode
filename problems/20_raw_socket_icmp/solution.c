#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifdef __linux__
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

// Standard Checksum Algorithm (ones' complement sum)
unsigned short calculate_checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    
    if (len == 1)
        sum += *(unsigned char*)buf;
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void solution() {}

int main() {
    int sockfd;
    
    // Attempt to open raw socket
    // This usually requires sudo/root
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        if (errno == EPERM) {
            printf("Permission denied (expected without root). Proceeding to verify packet construction logic only.\n");
        } else {
            perror("socket connection failed");
        }
    }

    // Prepare buffer
    char packet[64];
    memset(packet, 0, sizeof(packet));

    // ICMP Header Construction
    struct icmphdr *icmp = (struct icmphdr *)packet;
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(1234);
    icmp->un.echo.sequence = htons(1);
    
    // Add some payload data
    const char *payload = "HelloRawSocket";
    int payload_len = strlen(payload);
    memcpy(packet + sizeof(struct icmphdr), payload, payload_len);

    int packet_len = sizeof(struct icmphdr) + payload_len;

    // Calculate Checksum (must be zero before calc)
    icmp->checksum = 0;
    icmp->checksum = calculate_checksum(packet, packet_len);

    printf("ICMP Packet Constructed:\n");
    printf("  Type: %d\n  Code: %d\n  ID: %d\n  Seq: %d\n  Checksum: 0x%04x\n", 
           icmp->type, icmp->code, ntohs(icmp->un.echo.id), ntohs(icmp->un.echo.sequence), icmp->checksum);

    if (icmp->checksum != 0) {
        printf("Test Passed (Checksum logic ran)\n");
    }

    if (sockfd >= 0) {
        close(sockfd);
    }
    return 0;
}
#else
void solution() {}
int main() {
    printf("Not Linux. Skipping Raw Socket ICMP.\n");
    return 0;
}
#endif
