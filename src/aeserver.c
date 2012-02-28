#include "aeserver.h"
#include <stdio.h>

aeServer server;

int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    AESERVER_NOTUSED(eveltLoop);
    AESERVER_NOTUSED(id);
    AESERVER_NOTUSED(clientData);

    if (!(server.cronloops%100)) fprintf(stderr,"di da di da...\n");
    server.cronloops++;
    return 100;
}

void initServerConfig() {
    server.port = AESERVER_PORT;
    server.maxclients = AESERVER_MAX_CLIENTS;
    server.ipfd = -1;
    server.bindaddr = NULL;
}

void initServer() {
    server.el = aeCreateEventLoop(server.maxclients+1024);
    if (server.port != 0) {
        server.ipfd = anetTcpServer(server.neterr,server.port,server.bindaddr);
        if (server.ipfd == ANET_ERR) {
            fprintf(stderr, "Opening port %d: %s\n",server.port, server.neterr);
            exit(1);
        }
    }
    server.cronloops = 0;
    aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
    if (server.ipfd > 0 && aeCreateFileEvent(server.el, server.ipfd, AE_READABLE, acceptTcpHandler, NULL) == AE_ERR)
    {
        fprintf(stderr, "creating file event failed");
        exit(1);
    }
}

void beforeSleep(struct aeEventLoop *eventloop) {
    AESERVER_NOTUSED(eventloop);
    fprintf(stderr,"before sleep function is called......\n");
}

int main(void) {
    initServerConfig();
    initServer();
    aeSetBeforeSleepProc(server.el, beforeSleep);
    aeMain(server.el);
    aeDeleteEventLoop(server.el);    
}
