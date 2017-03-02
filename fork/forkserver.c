#include "include/socket.h"

#include <string.h>
#include <time.h>

#define PORT 2929

int
main(int argc, const char *argv[])
{
    int listenfd, connfd;
    char buf[BUFSIZ];
    time_t ticks;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: a.out IPaddress\n");

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port   = htons(PORT);

    printf("Start serving on http://%s:%d ...\n", argv[1], PORT);

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    for (;;) {
        connfd = Accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buf, sizeof(buf),
                 "HTTP/1.0 200 OK\r\n\r\n%.24s\r\n", ctime(&ticks));
        Write(connfd, buf, strlen(buf));
        printf("[log] new request\n");

        Close(connfd);
    }

    return 0;
}
