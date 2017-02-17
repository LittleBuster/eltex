#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
 

int main(int argc, char **argv)
{
    int sockfd;
    int n, len;
    char sendline[1000];
    struct sockaddr_in servaddr, cliaddr;

    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        puts("Socket error");
        exit(1);
    }

    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
        puts("error sockopt");
        exit(1);
    }

    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(0);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
    if(bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5001);
 
    if(inet_aton("192.168.1.255", &servaddr.sin_addr) == 0)
    {
        printf("Invalid IP address\n");
        close(sockfd); /* По окончании работы закрываем дескриптор сокета */
        exit(1);
    }
 
    strcpy(sendline, "Hello world");

    if(sendto(sockfd, sendline, strlen(sendline) + 1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    close(sockfd);
 
    return 0;
}


/*int create_socket(int port)
{
	struct sockaddr_in saddr;
    int s;
    int slen = sizeof(saddr);
    char buf[20];
    char message[20];
 
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        puts("fail");
        return -1;
    }

    int broadcast = 1;
    if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
        puts("error sockopt");
        exit(1);
    }
 
    memset((char *)&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(5001);
     
    if (inet_aton("192.168.1.255", &saddr.sin_addr) == 0) 
    {
        puts("fail2");
        exit(1);
    }

    strcpy(message, "Ww");
    if (sendto(s, message, strlen(message), 0, (struct sockaddr *)&saddr, slen)==-1) {
        puts("fail sendto");
    }
    close(s);
}

int main(int argc, char const *argv[])
{
    
    return 0;
}*/