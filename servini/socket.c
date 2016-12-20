#include <string.h>
#include <time.h>

#include "socket.h"

int
main(int argc, const char *argv[])
{
    int listenfd, connfd;
    char recvline[MAXLINE + 1];
    char buf[BUFSIZ];
    time_t ticks;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: a.out <IPaddress> 2929\n");

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port   = htons(2929);

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for (;;) {
        connfd = Accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buf, sizeof(buf),
                 "HTTP/1.1 200 OK\r\n\r\n%.24s\r\n", ctime(&ticks));
        Write(connfd, buf, strlen(buf));
        fputs(buf, stdout);

        Close(connfd);
    }

    return 0;
}
