#ifndef _SOCKET_H_
#define _SOCKET_H_

int set_nonblocking(int fd);

int set_blocking(int fd);

#if 0
int sock_bind_wild(int fd, int family);

int sock_cmp_addr(const struct sockaddr *addr1,
        const struct sockaddr *addr2, socklen_t len);

int sock_cmp_port(const struct sockaddr *addr1,
        const struct sockaddr *addr2, socklen_t len);

int sock_get_port(const struct sockaddr *addr, socklen_t len);

char * sock_ntop(const struct sockaddr *addr, socklen_t len);

void sock_set_addr(struct sockaddr *addr, socklen_t len, void *ptr);

void sock_set_port(struct sockaddr *addr, socklen_t len, int port);

void sock_set_wild(struct sockaddr *sockaddr, socklen_t len);
#endif


#endif

