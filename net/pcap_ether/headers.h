// Packet header sniffer
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdint.h>


struct EthHeader {
    uint8_t dest[6];
    uint8_t src[6];
    uint16_t type;
} __attribute__((packed));


struct IpHeader {
    uint8_t version:4;
    uint8_t header_length:4;
    uint8_t service_type;
    uint16_t total_length;

    /* Fragmentation */
    uint16_t identify;
    uint8_t flags:3;
    uint16_t offset:13;

    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t source;
    uint32_t destination;
} __attribute__((packed));


struct UdpHeader {
    uint16_t source_port;
    uint16_t destination_port;
    uint16_t len;
    uint16_t checksum;
} __attribute__((packed));

struct QuasiUdpHeader {
    uint32_t source;
    uint32_t destination;
    uint8_t reserv;
    uint8_t protocol;
    uint16_t udp_len;
} __attribute__((packed));


#endif
