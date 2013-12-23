#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

ssize_t
readn(int fd, void *buf, size_t n)
{
    ssize_t left, len;
    char *ptr;

    ptr = buf;
    left = n;
    while (left > 0) {
        if ((len = read(fd, ptr, left)) < 0) {
            if (errno == EINTR) {
                len = 0;
            } else {
                return -1;
            }
        } else if (len == 0) {
            break;
        }
        left -= len;
        ptr += len;
    }

    return (n - left);
}

ssize_t
writen(int fd, const void *buf, size_t n)
{
    ssize_t left, len;
    const char *ptr;

    ptr = buf;
    left = n;
    while (left > 0) {
        if ((len = write(fd, ptr, left)) <= 0) {
            if (errno == EINTR) {
                len = 0;
            } else {
                return -1;
            }
        }
        left -= len;
        ptr += len;
    }
    return n;
}

