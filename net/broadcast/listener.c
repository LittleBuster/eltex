#include <sys/epoll.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    int i;
    int sockfd;
    int clilen, n;
    char line[12];
    struct sockaddr_in servaddr, cliaddr;
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5001);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        puts("Socket fail");
        exit(1);
    }
 
    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        puts("Binding fail");
        close(sockfd);
        exit(1);
    }
 
    for (;;) {
        clilen = sizeof(cliaddr);
        if((n = recvfrom(sockfd, line, 11, 0, (struct sockaddr *)&cliaddr, &clilen)) < 0)
        {
            puts("Error receiving");
            close(sockfd);
            exit(1);
        }
        puts(line);
 
    }
    return 0;
}