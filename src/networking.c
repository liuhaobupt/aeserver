#include "aeserver.h"
#include "ae.h"
#include "anet.h"

#include <stdlib.h>
#include <stdio.h>

void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
    aeClient *c = (aeClient*) privdata;
    int nread, readlen;
    size_t qblen;
    AESERVER_NOTUSED(el);
    AESERVER_NOTUSED(mask);

    fprintf(stderr,"readQueryFromClient function is called\n");
}

aeClient *createClient(int fd) {
    aeClient *c = malloc(sizeof(aeClient));
    c->fd = fd;

    if (fd != -1) {
        anetNonBlock(NULL,fd);
        if (aeCreateFileEvent(server.el,fd,AE_READABLE,readQueryFromClient,c) == AE_ERR)
        {
            close(fd);
            free(c);
            return NULL;
        }
    }
    return c;
}


static void acceptCommonHandler(int fd) {
    struct aeClient *c;
    if ((c = createClient(fd)) == NULL) {
        fprintf(stderr,"Error allocating resoures for the client");
        close(fd); /* May be already closed, just ingore errors */
        return;
    }
}

void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    int cport, cfd;
    char cip[128];
    AESERVER_NOTUSED(el);
    AESERVER_NOTUSED(mask);
    AESERVER_NOTUSED(privdata);

    cfd = anetTcpAccept(server.neterr, fd, cip, &cport);
    if (cfd == AE_ERR) {
        fprintf(stderr,"Accepting client connection: %s", server.neterr);
        return;
    }
    fprintf(stderr,"Accepted %s:%d", cip, cport);
    acceptCommonHandler(cfd);
}

