#include <stdlib.h>
#include <stdio.h>

#include "config.h"
/* #include "server.h" */


int main(int argc, char **argv)
{
    struct server srv;

    if (load_config(&srv, "server.cfg") != 0) {
        fprintf(stderr, "load_config failed");
        return -1;
    }

    if (server_init(&srv) != 0) {
        fprintf(stderr, "server_init failed");
        return -1;
    }

    if (server_start(&srv) != 0) {
        fprintf(stderr, "server_start failed");
        server_destroy(&srv);
        return -1;
    }

    server_destroy(&srv);

    return 0;
}
