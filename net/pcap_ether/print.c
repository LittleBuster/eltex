// Packet header sniffer
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include "print.h"
#include "headers.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <string.h>


static void ShowMac(const char *text, const unsigned char *mac)
{
    printf("%s", text);
    for (unsigned char i = 0; i < 7; i++) {
        printf("%02X", mac[i]);
        if (i != 6)
            printf(":");
    }
    printf("\n");
}

static void ShowPayload(const unsigned char *data, unsigned size)
{
    unsigned sz = size - sizeof(struct EthHeader);

    printf("Payload:\n");
    for (unsigned i = 0; i < sz; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void ShowDevices(pcap_if_t *alldevsp)
{
    pcap_if_t *device;
    unsigned i = 0;

    for(device = alldevsp; device != NULL; device = device->next) {
        printf("%d. %s - %s\n", i, device->name, device->description);
        i++;
    }
}

void ShowMacHdr(const unsigned char *buff, unsigned size)
{
    struct EthHeader *eth = (struct EthHeader *)buff;

    ShowMac("Dst MAC: ", eth->dest);
    ShowMac("Src MAC: ", eth->src);
    printf("Type: %u\n", eth->type);
    ShowPayload(buff, size);
}

unsigned ShowIPHdr(const unsigned char *buff, struct QuasiUdpHeader *hdr)
{
    struct sockaddr_in source, dest;
    struct IpHeader *iph = (struct IpHeader *)(buff + sizeof(struct EthHeader));

    memset(&source, 0, sizeof(source));
    memset(&dest, 0, sizeof(dest));

    source.sin_addr.s_addr = iph->source;
    dest.sin_addr.s_addr = iph->destination;

    printf("Dst IP: %s\n" , inet_ntoa(dest.sin_addr));
    printf("Src IP: %s\n" , inet_ntoa(source.sin_addr));
    switch (iph->protocol) {
        case 1: {
            puts("Protocol: ICMP");
            break;
        }
        case 4: {
            puts("Protocol: IP");
            break;
        }
        case 6: {
            puts("Protocol: TCP");
            break;
        }
        case 17: {
            puts("Protocol: UDP");
            break;
        }
    }

    hdr->source = iph->source;
    hdr->destination = iph->destination;
    hdr->udp_len = 8;
    hdr->protocol = 17;
    hdr->reserv = 0;

    return iph->header_length;
}

bool getUDP(const unsigned char *buff)
{
    struct IpHeader *iph = (struct IpHeader *)(buff + sizeof(struct EthHeader));

    if (iph->protocol == 17) {
        return true;
    }
    return false;
}

void ShowUDPHdr(const unsigned char *buff, unsigned size, const struct QuasiUdpHeader *hdr)
{
    struct UdpHeader *udh = (struct UdpHeader *)(buff + sizeof(struct EthHeader) + size);

    printf("Src Port: %u\n", udh->source_port);
    printf("Dst Port: %u\n", udh->destination_port);
    printf("Checksum: %u\n", udh->checksum);
}
