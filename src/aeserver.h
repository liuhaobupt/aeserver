#ifndef __AESERVER_H
#define __AESERVER_H

#include "ae.h"
#include "anet.h"

/* Error codes */
#define AESERVER_OK             0
#define AESERVER_ERR            -1

#define AESERVER_PORT           6380
#define AESERVER_MAX_CLIENTS    10000

/* Anti-warning macro... */
#define AESERVER_NOTUSED(V)    ((void) V)

struct aeClient;

typedef struct aeServer {
    aeEventLoop *el;
    unsigned int maxclients;
    int port;
    char *bindaddr;
    int ipfd;

    char neterr[ANET_ERR_LEN];
    unsigned int cronloops;
    struct aeClient *current_client;
}aeServer;

typedef struct aeClient {
    int fd;
}aeClient;

extern aeServer server;

void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);

#endif /* __AESERVER__H */
