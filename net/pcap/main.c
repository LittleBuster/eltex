// Packet sniffer
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <pcap.h>
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


pcap_t *handle;


static void ShowIP(unsigned char *buff, int sz)
{
    unsigned short iphdrlen;
    struct sockaddr_in source, dest;       
    struct iphdr *iph = (struct iphdr *)(buff  + sizeof(struct ethhdr));
    iphdrlen = iph->ihl * 4;
     
    memset(&source, 0, sizeof(source));
    memset(&dest, 0, sizeof(dest));
    source.sin_addr.s_addr = iph->saddr;
    dest.sin_addr.s_addr = iph->daddr;

    printf("Source IP: %s\n" , inet_ntoa(source.sin_addr));
    printf("Destination IP: %s\n" , inet_ntoa(dest.sin_addr));
}

static void ShowICMP(const unsigned char *buff, int sz)
{
	unsigned short iphdrlen; 
    struct iphdr *iph = (struct iphdr *)(buff  + sizeof(struct ethhdr));
    iphdrlen = iph->ihl * 4; 
    struct icmphdr *icmph = (struct icmphdr *)(buff + iphdrlen  + sizeof(struct ethhdr));
    int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof icmph;
     
    puts("========== ICMP Packet ===========");
             
    if ((unsigned int)(icmph->type) == 11) {
    	puts("Type: TTL Expired");
    }
    else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY) {
    	puts("Type: ECHO Reply");
    }
     
    printf("Code: %u\n", (unsigned)(icmph->code));
    printf("Checksum: %d\n", ntohs(icmph->checksum));

    ShowIP(buff, sz);

    puts("==================================");
}

static void ProcessPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *buff)
{
    int size = header->len;
    struct iphdr *iph = (struct iphdr *)(buff + sizeof(struct ethhdr));

    switch (iph->protocol) {
        case 1:
        	//ICMP
        	puts("New ICMP packet founded!");
        	ShowICMP(buff, size);
            break;
    }
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