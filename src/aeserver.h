#ifndef __AESERVER_H
#define __AESERVER_H

#include "ae.h"

/* Error codes */
#define AESERVER_OK             0
#define AESERVER_ERR            -1

#define AESERVER_PORT           6380
#define AESERVER_MAX_CLIENTS    10000

/* Anti-warning macro... */
#define REDIS_NOTUSED(V)    ((void) V)

struct aeServer {
    aeEventLoop *el;
    unsigned int maxclients;
    int port;
    char *bindaddr;
    int ipfd;

    char neterr[ANET_ERR_LEN];
    unsigned int cronloops;
};

extern aeServer server;

#endif
