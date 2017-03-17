// Raw udp socket
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

#include "headers.h"


static unsigned short Checksum(unsigned short *ptr,int nbytes)
{
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while(nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if(nbytes == 1) {
        oddbyte = 0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }

    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;

    return(answer);
}

int main(void)
{
    struct sockaddr_in sin;
    struct QuasiUdpHeader psh;
    char datagram[4096] , source_ip[32] , *data , *pseudogram;

    int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(s == -1) {
        puts("Fail socket creation.");
        return -1;
    }
    memset (datagram, 0, 4096);
    struct iphdr *iph = (struct iphdr *) datagram;
    struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));

    data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(data , "MYMSG11111X");
    strcpy(source_ip , "127.0.0.1");

    sin.sin_family = AF_INET;
    sin.sin_port = htons(5001);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(data);
    iph->id = htonl(54321);
    iph->frag_off = 0;
    iph->ttl = 255;
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = inet_addr(source_ip);
    iph->daddr = sin.sin_addr.s_addr;
    iph->check = Checksum((unsigned short *) datagram, iph->tot_len);

    udph->source = htons (5001);
    udph->dest = htons (5001);
    udph->len = htons(8 + strlen(data));
    udph->check = 0;

    psh.source_address = inet_addr( source_ip );
    psh.dest_address = sin.sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + strlen(data) );

    int psize = sizeof(struct QuasiUdpHeader) + sizeof(struct udphdr) + strlen(data);
    pseudogram = malloc(psize);

    memcpy(pseudogram , (char *)&psh , sizeof (struct QuasiUdpHeader));
    memcpy(pseudogram + sizeof(struct QuasiUdpHeader) , udph , sizeof(struct udphdr) + strlen(data));

    udph->check = Checksum((unsigned short *)pseudogram , psize);

    if (sendto (s, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0) {
         puts("Fail sending");
    } else {
        printf ("Packet sended. Length : %d \n" , iph->tot_len);
    }
    return 0;
}
