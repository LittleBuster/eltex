#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include <unistd.h>
#include <string.h>


#define EPOLL_MAX 1

int main(void)
{
	int epfd;
	int srv_fd;
	int ret_val;
	int enable = 1;
	struct epoll_event ep_ev, new_ev;
	struct sockaddr_in srv_addr;

	epfd = epoll_create(EPOLL_MAX);
	ep_ev.events = EPOLLIN;

	srv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (srv_fd < 0)
		return -1;

	epoll_ctl(epfd, EPOLL_CTL_ADD, srv_fd, &ep_ev);

	ret_val = setsockopt(srv_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	if (ret_val < 0)
		return -1;

	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	sock_addr.sin_port = htons(5000);

	ret_val = bind(srv_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret_val == -1)
        return -1;

    ret_val = listen(srv_fd, 1);
    if (ret_val == -1)
        return -1;

   // for (;;) {
    	ret_val = epoll_wait(epfd, &new_ev, EPOLL_MAX, -1);
    //}
	return 0;
}