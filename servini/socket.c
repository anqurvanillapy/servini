#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#define MAXLINE 4096  /* max text line length */

#define err_quit(errmsg) do {   \
    fputs(errmsg, stdout);      \
    exit(EXIT_FAILURE);         \
} while(0)

#define err_sys(errmsg) do {    \
    perror(errmsg);             \
    exit(EXIT_FAILURE);         \
} while(0)

int
main(int argc, const char *argv[])
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    char sendbuf[BUFSIZ];
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("not enough arguments\n");

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    sprintf(sendbuf, "GET /get\r\n\r\n");  // Hello, HTTP!
    fputs(sendbuf, stdout);
    bzero(&servaddr, sizeof(servaddr)); // filling w/ 0s like memset
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(80);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit(argv[1]);

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connection error");

    if (send(sockfd, sendbuf, sizeof(sendbuf), 0) < 0)
        err_sys("send error");

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;    /* null terminator */
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        err_sys("read error");

    return 0;
}
