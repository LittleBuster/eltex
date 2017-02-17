// Multicast UDP listener
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int BindMulticastSocket(const char *ip, unsigned port, struct sockaddr_in *claddr)
{
    struct ip_mreq mreq;
    int fd;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        puts("Socket error");
        return -1;
    }

    claddr->sin_family = AF_INET;
    claddr->sin_port = htons(port);
    claddr->sin_addr.s_addr = htonl(INADDR_ANY);
 
    if(bind(fd, (struct sockaddr *)claddr, sizeof(struct sockaddr_in)) < 0) {
        puts("Fail binding server.");
        close(fd);
        return -1;
    }

    bzero(&mreq, sizeof(mreq));
    if (inet_aton(ip, &mreq.imr_multiaddr) < 0) {
        puts("Fail ip aton");
        return -1;
    }
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        puts("Set sockopt error.");
        return -1;
    }
    return fd;
}

int main(void)
{
    unsigned sz;
    int fd;
    char buf[12];
    struct sockaddr_in claddr;

    fd = BindMulticastSocket("224.0.1.1", 5001, &claddr);
    sz = sizeof(claddr);

    for(;;) {
        if ((recvfrom(fd, buf, 11, 0, (struct sockaddr *)&claddr, &sz)) < 0) {
            puts("Fail receiving data.");
        }
        printf("Receiving: %s\n", buf);
    }
}
