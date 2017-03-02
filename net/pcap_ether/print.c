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


void ShowMac(const char *text, const unsigned char *mac)
{
    printf("%s", text);
    for (unsigned char i = 0; i < 7; i++) {
        printf("%02X", mac[i]);
        if (i != 6)
            printf(":");
    }
    printf("\n");
}

void ShowPayload(const unsigned char *data, unsigned size)
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

void ShowIP(const unsigned char *buff)
{
    struct sockaddr_in source, dest;
    struct IpHeader *iph = (struct IpHeader *)buff;

    memset(&source, 0, sizeof(source));
    memset(&dest, 0, sizeof(dest));

    source.sin_addr.s_addr = iph->source;
    dest.sin_addr.s_addr = iph->destination;

    printf("Source IP: %s\n" , inet_ntoa(source.sin_addr));
    printf("Destination IP: %s\n" , inet_ntoa(dest.sin_addr));
}
