// Packet header sniffer
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>

#include <pcap.h>

#include "headers.h"
#include "print.h"


pcap_t *handle;


static void ProcessPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *buff)
{
    bool isUdp;
    unsigned size = header->len;
    unsigned iplen;
    struct QuasiUdpHeader qhdr;

    isUdp = getUDP(buff);
    if (isUdp) {
        puts("============ Packet ==============");
        ShowMacHdr(buff, size);
        iplen = ShowIPHdr(buff, &qhdr);
        ShowUDPHdr(buff, iplen, &qhdr);
        puts("==================================");
    }
}

void SniffDevice(unsigned dev_number, pcap_if_t *alldevsp)
{
	pcap_if_t *device;
	unsigned i = 0;
	char errbuf[100];

	for(device = alldevsp; device != NULL; device = device->next) {
		if (i == dev_number) {
			handle = pcap_open_live(device->name, 65536, 1, 0, errbuf);
			if (handle == NULL) {
				puts("Fail opening device for sniffing.");
				break;
			}
			pcap_loop(handle , -1, ProcessPacket, NULL);
			break;
		}
        i++;
    }
    struct iphdr p;
}


int main(void)
{
	pcap_if_t *alldevsp;
    pcap_t *handle; 	
    char errbuf[100];

    if(pcap_findalldevs(&alldevsp , errbuf)) {
        printf("Fail finding devices: %s" , errbuf);
        return -1;
    }

    for (;;) {
    	char cmd[255];

    	puts("===================================");
    	puts("[1] Show all devices");
    	puts("[2] Sniff device");
    	puts("===================================");

    	printf("%s", ">");
    	scanf("%s", cmd);

    	if (!strcmp(cmd, "1")) {
    		ShowDevices(alldevsp);
    	}
    	if (!strcmp(cmd, "2")) {
    		char dev[255];
    		unsigned dev_num;

    		printf("device>");
    		scanf("%s", dev);
    		sscanf(dev, "%u", &dev_num);

    		SniffDevice(dev_num, alldevsp);
    	}
    }
    
	return 0;
}
