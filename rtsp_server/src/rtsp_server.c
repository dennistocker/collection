#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

int
readall(int fd, char *buf, size_t len)
{
    char *tmp = buf;
    size_t count = len;
    while (1) {
        int n = read(fd, tmp, count);
        if (n == -1) {
            break;
        } else if (n == 0) {
            close(fd);
            break;
        }
        tmp += n;
        count -= n;
    }
}

int
writeall(int fd, const char *buf, size_t len)
{
    const char *tmp = buf;
    size_t count = len;
    while (1) {
        int n = write(fd, tmp, count);
        if (n == -1) {
            break;
        }
        tmp += n;
        count -= n;
    }
}

int set_nonblocking(int fd)
{
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        perror("getflags");
        return -1;
    }
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    return 0;
}

int main(int argc, char **argv)
{
    char buf[128];
    struct sockaddr_in server;
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int epoll_fd = epoll_create(1);

    set_nonblocking(listen_fd);

    int optval = 1;
    setsockopt(listen_fd,  SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(544);
    bind(listen_fd, (struct sockaddr*)&server, sizeof(server));

    listen(listen_fd, 128);

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev);

    int num = 0;
    while (1) {
        struct epoll_event evs[128], e;
        int n = epoll_wait(epoll_fd, evs, sizeof(evs)/sizeof(evs[0]), -1);
        printf("epoll_wait returned: %d\n", n);
        int i;
        for (i = 0; i < n; ++i) {
            e = evs[i];
            if (e.events & EPOLLIN) {
                if (e.data.fd == listen_fd) {
                    int conn_fd = accept(listen_fd, 0, 0);
                    printf("new connection: %d\n", conn_fd);
                    set_nonblocking(conn_fd);

                    memset(&ev, 0, sizeof(ev));
                    ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
                    ev.data.fd = conn_fd;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev);
                } else {
                    int n = readall(e.data.fd, buf, sizeof(buf));
                    printf("got message: %s\n", buf);
                }
            } else {
                printf("event: %u\n", ev.events);
            }
        }
    }

    return 0;
}

