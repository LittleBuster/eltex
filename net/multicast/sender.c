// Multicast UDP sender
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int CreateUdpSocket(const char *ip, unsigned port, struct sockaddr_in *srvaddr)
{
    int fd;

    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        puts("Socket creation error");
        return -1;
    }

    bzero(srvaddr, sizeof(struct sockaddr_in));
    srvaddr->sin_family = AF_INET;
    srvaddr->sin_port = htons(port);
 
    if(inet_aton(ip, &srvaddr->sin_addr) == 0) {
        puts("Invalid IP address");
        close(fd);
        return -1;
    }
    return fd;
}

int main(void)
{
    int fd;
    char text[12];
    struct sockaddr_in srvaddr;

    fd = CreateUdpSocket("224.0.1.1", 5001, &srvaddr);
    if (fd == -1)
        return -1;
    strncpy(text, "Hello world", 11);

    if(sendto(fd, text, strlen(text)+1, 0, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) < 0) {
        puts("Fail sending multicast data.");
        close(fd);
        return -1;
    }
    puts("Multicast data sended.");
    close(fd);
    return 0;
}