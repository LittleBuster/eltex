// Packet header sniffer
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#ifndef PRINT_H_
#define PRINT_H_

#include <pcap.h>
#include <stdbool.h>

#include "headers.h"


void ShowDevices(pcap_if_t *alldevsp);

bool getUDP(const unsigned char *buff);

unsigned ShowIPHdr(const unsigned char *buff, struct QuasiUdpHeader *hdr);

void ShowMacHdr(const unsigned char *buff, unsigned size);

void ShowUDPHdr(const unsigned char *buff, unsigned size, const struct QuasiUdpHeader *hdr);


#endif
