#ifndef _SERVER_H_
#define _SERVER_H_

struct server {
    /* config */
    int port;

    /**/
    int ep_fd;
};

int server_init(struct server *srv);

int server_start(struct server *srv);

int server_destroy(struct server *srv);

#endif

