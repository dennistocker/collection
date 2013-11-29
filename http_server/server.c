#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "server.h"
#include "socket.h"

int server_init(struct server *srv)
{
    assert(srv);
    memset(srv, 0, sizeof(*srv));
    srv->ep_fd = epoll_create(10);
    if (srv->ep_fd == -1) {
        perror("epoll_create failed:");
        return -1;
    }

    return 0;
}

int server_start(struct server *srv)
{
    int fd;
    int reuseaddr = 1;

    assert(srv);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket failed:");
        goto failed;
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                (const void *)&reuseaddr, sizeof(reuseaddr)) == -1) {
        perror("set reuseaddr failed:") ;
        goto failed;
    }
    if (set_nonblocking(fd) != 0) {
        perror("set_nonblocking failed");
        goto failed;
    }
    listen(fd, 128);


    return 0;

failed:
    if (fd > 0) {
        close(fd);
    }
    return -1;
}


int server_destroy(struct server *srv)
{
    assert(srv);

}



