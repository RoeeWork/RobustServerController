#include <stdio.h>
#include <stdlib.h>

#define PROTO_ARP 0x0806
#define HW_TYPE 1
#define MAC_LENGTH 6
#define IPV4_LENGTH 4
#define ARP_REQUEST 0x01
#define ARP_REPLY 0x02

struct arp_package {
    unsigned short hw_type;
    unsigned short protocol_type;
    unsigned char hw_len;
    unsigned char protocol_len;
    unsigned short operation;
    unsigned char src_mac[MAC_LENGTH];
    unsigned char src_ip[IPV4_LENGTH];
    unsigned char dst_mac[MAC_LENGTH];
    unsigned char dst_ip[IPV4_LENGTH];
};

