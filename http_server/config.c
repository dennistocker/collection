#include <assert.h>

#include "config.h"


int load_config(struct server *srv, const char *conf)
{
    assert(srv);

    srv->port = 8010;

    return 0;
}
