
#include <stdio.h>
#include <fcntl.h>

#include "socket.h"

int set_nonblocking(int fd)
{
    int flags;

    if ((flags = fcntl(fd, F_GETFL, 0)) < 0) {
        perror("get socket flag failed:");
        return -1;
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        perror("set socket flag failed:");
        return -1;
    }

    return 0;
}

int set_blocking(int fd)
{
    int flags;

    if ((flags = fcntl(fd, F_GETFL, 0)) < 0) {
        perror("get socket flag failed:");
        return -1;
    }
    flags &= ~O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        perror("set socket flag failed:");
        return -1;
    }

    return 0;
}

