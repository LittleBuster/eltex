#include <sys/epoll.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int create_socket(int port)
{
	int ret_val;
    struct sockaddr_in sock_addr;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        return -1;

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(port);

    ret_val = bind(fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret_val == -1)
        return -1;

    ret_val = listen(fd, 2);
    if (ret_val == -1)
        return -1;
    return fd;
}

int main(int argc, char const *argv[])
{
    int epfd;
    int fd[10];
    int port = 5000;

    epfd = epoll_create(10);

    for (int i = 0; i < 10; i++) {
    	struct epoll_event ep_ev;

    	ep_ev.events = EPOLLIN;

    	fd[i] = create_socket(port+i);
    	epoll_ctl(epfd, EPOLL_CTL_ADD, fd[i], &ep_ev);
    }

    struct epoll_event ev;
    for (;;) {
    	int ret = epoll_wait(epfd, &ev, 10, 100);
    	if (ret == 1) {
    		char buf[1];

    		puts("New event!");
    		read(ev.data.fd, buf, 1);
    		puts(buf);
    		break;
    	}
    }
}