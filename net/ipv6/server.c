// IPv6 socket example
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


static const uint8_t myaddr[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };


int main(void)
{
	int ret_val;
    struct sockaddr_in6 srvaddr;

    int fd = socket(AF_INET6, SOCK_STREAM, 0);

    memset(&srvaddr, 0x00, sizeof(srvaddr));
    srvaddr.sin6_family = AF_INET6;
    memcpy(srvaddr.sin6_addr.s6_addr, myaddr, sizeof(myaddr));
    srvaddr.sin6_port = htons(5000);

    ret_val = bind(fd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
    if (ret_val < 0) {
        puts("Fail binding.");
        return -1;
    }

    ret_val = listen(fd, 2);
    if (ret_val < 0) {
        puts("Fail listening.");
        return -1;
    }    

    for (;;) {
        char buf[20];

        int client = accept(fd, NULL, NULL);
        if (client < 0) {
            puts("Fail accepting.");
            continue;
        }
        ret_val = read(client, buf, 20);
        puts(buf);
    }
}